# Michael Coughlin
# hiimmichael.com
# 2019

import ipaddress
import socket
import subprocess
import sys
import time
import webbrowser


def loading_bar(length):
    loading = ''
    for j in range(0, length - 1):
        loading += '-'
    loading += ']'
    bar = ''
    temp = '['
    for i in range(length):
        time.sleep(0.03)
        temp += '#'
        bar = temp
        bar += loading[i:length]
        sys.stdout.write("\r" + bar)
        sys.stdout.flush()


def hilite(string, status, bold):
    attr = []
    if status:
        # green
        attr.append('32')
    else:
        # red
        attr.append('31')
    if bold:
        attr.append('1')
    return '\x1b[%sm%s\x1b[0m' % (';'.join(attr), string)


s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.connect(("8.8.8.8", 80))
net_addr = s.getsockname()[0].rpartition('.')[0] + '.0/24'
port = 80
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Create the network
ip_net = ipaddress.ip_network(unicode(net_addr))

# Get all hosts on that network
all_hosts = list(ip_net.hosts())

# Configure subprocess to hide the console window
info = subprocess.STARTUPINFO()
info.dwFlags |= subprocess.STARTF_USESHOWWINDOW
info.wShowWindow = subprocess.SW_HIDE

print("""
      ___          _          ___  _
     |   \ ____  _(_)__ ___  |   \(_)_____ _____ _____ _ _ _  _
     | |) / -_\ V | / _/ -_) | |) | (_-/ _/ _ \ V / -_| '_| || |
     |___/\___|\_/|_\__\___| |___/|_/__\__\___/\_/\___|_|  \_, |
                                                           |__/
                                                            v1.1
        """)
print 'Current local network: ' + str(net_addr) + '\n'
print 'Menu:'
print ' (A) Scan network for devices on Port 8080'
print ' (B) Scan network for devices on Port 80\n'

while True:
    selected_option = raw_input('Please enter the letter of a command and press enter: \n ')
    if selected_option == 'A':
        port = 8080
        break
    elif selected_option == 'B':
        port = 80
        break
    else:
        print '\nUnrecognized input, please try again (e.g. A)'

loading_bar(40)
print "\nSearching for Devices\n"

active_devices = {}

# For each IP address in the subnet,
# run the ping command with subprocess.popen interface
for i in range(len(all_hosts)):
    output = subprocess.Popen(['ping', '-n', '1', '-w', '500', str(all_hosts[i])], stdout=subprocess.PIPE,
                              startupinfo=info).communicate()[0]
    print("Interrogating " + str(all_hosts[i]))
    if "Destination host unreachable" not in output.decode('utf-8') and "Request timed out" not in output.decode(
            'utf-8'):
        result = sock.connect_ex((str(all_hosts[i]), port))
        # or send UDP message - if reply then open, set time, etc.
        print '              ' + hilite((str(all_hosts[i]) + " Active Device"), True, False)
        if result == 0:
            print hilite(('              Port ' + str(port) + ' Active'), True, True)
            active_devices[str(all_hosts[i])] = 'Device Active/Port Active'
            webbrowser.open('http://' + str(all_hosts[i]) + ':' + str(port), new=2)
        else:
            print hilite(('              Port ' + str(port) + ' Inactive'), False, False)
            active_devices[str(all_hosts[i])] = 'Device Active/Port Inactive'

print '\nResults:'
for kv in active_devices.items():
    print kv[0], '\t', kv[1]

print ' \nGood day!'
