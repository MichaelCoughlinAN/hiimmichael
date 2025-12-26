import socket
import struct
import logging
import hmac
import hashlib

# Basic STUN constants
STUN_MAGIC_COOKIE = 0x2112A442
STUN_BINDING_REQUEST = 0x0001
STUN_BINDING_RESPONSE_SUCCESS = 0x0101
STUN_ATTRIBUTE_XOR_MAPPED_ADDRESS = 0x0020
STUN_ATTRIBUTE_MESSAGE_INTEGRITY = 0x0008
STUN_ATTRIBUTE_FINGERPRINT = 0x8028
STUN_ATTRIBUTE_USERNAME = 0x0006
STUN_ATTRIBUTE_SOFTWARE = 0x8022
STUN_ATTRIBUTE_ERROR_CODE = 0x0009

# Initialize logging
logging.basicConfig(level=logging.INFO)

def hmac_sha1(key, message):
    return hmac.new(key, message, hashlib.sha1).digest()

def calculate_message_integrity(data, key):
    return hmac_sha1(key, data)

def pack_xor_address(family, port, address, magic_cookie, transaction_id):
    if family == socket.AF_INET:
        xport = port ^ (magic_cookie >> 16)
        xaddress = struct.unpack("!I", socket.inet_aton(address))[0] ^ magic_cookie
        return struct.pack("!BBH4s", 0, 1, xport, struct.pack("!I", xaddress))
    elif family == socket.AF_INET6:
        xport = port ^ (magic_cookie >> 16)
        xaddress = struct.unpack("!QQ", socket.inet_pton(socket.AF_INET6, address))
        xaddress = (xaddress[0] ^ (magic_cookie << 32), xaddress[1] ^ int.from_bytes(transaction_id[:4], 'big'))
        return struct.pack("!BBH16s", 0, 2, xport, struct.pack("!QQ", *xaddress))
    else:
        raise ValueError("Unsupported address family")

def create_response(transaction_id, attributes):
    message_length = sum(len(attr) for attr in attributes)
    response_header = struct.pack("!HHI", STUN_BINDING_RESPONSE_SUCCESS, message_length, STUN_MAGIC_COOKIE)
    return response_header + transaction_id + b''.join(attributes)

def handle_stun_message(data, client_address, secret_key):
    try:
        header = struct.unpack("!HHI12s", data[:20])
        message_type, message_length, magic_cookie, transaction_id = header

        if magic_cookie != STUN_MAGIC_COOKIE:
            logging.error("Invalid magic cookie from %s", client_address)
            return None

        attributes = []
        if message_type == STUN_BINDING_REQUEST:
            logging.info("STUN Binding Request received from %s", client_address)
            family = socket.AF_INET if '.' in client_address[0] else socket.AF_INET6
            xor_mapped_address = pack_xor_address(family, client_address[1], client_address[0], magic_cookie, transaction_id)
            attributes.append(struct.pack("!HH", STUN_ATTRIBUTE_XOR_MAPPED_ADDRESS, len(xor_mapped_address)) + xor_mapped_address)

            # Append additional attributes if needed
            # For MESSAGE-INTEGRITY, you would calculate this after forming the initial part of the message
            # For simplicity, I am skipping USERNAME and FINGERPRINT in this example

            message_wo_mi = create_response(transaction_id, attributes)
            message_integrity = calculate_message_integrity(message_wo_mi + struct.pack("!HH", STUN_ATTRIBUTE_MESSAGE_INTEGRITY, 20), secret_key)
            attributes.append(struct.pack("!HH20s", STUN_ATTRIBUTE_MESSAGE_INTEGRITY, 20, message_integrity))

            return message_wo_mi + attributes[-1]  # Reconstruct message with MESSAGE-INTEGRITY

        logging.warning("Unhandled STUN message type from %s: %x", client_address, message_type)
        return None

    except Exception as e:
        logging.error("Error processing STUN message from %s: %s", client_address, e)
        return None

def stun_server(secret_key):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(('', 3478))
    logging.info("STUN server listening on port 3478")

    while True:
        data, addr = sock.recvfrom(1024)
        response = handle_stun_message(data, addr, secret_key)
        if response:
            sock.sendto(response, addr)

if __name__ == '__main__':
    secret_key = b'secret'  # This should be securely generated and stored
    stun_server(secret_key)
    