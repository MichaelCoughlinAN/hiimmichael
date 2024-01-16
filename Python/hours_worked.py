from datetime import datetime, timedelta

def time_difference(start, end):
    fmt = '%I:%M %p'
    start_time = datetime.strptime(start, fmt)
    end_time = datetime.strptime(end, fmt)
    # Handling cases where end time is on the next day
    if end_time < start_time:
        end_time += timedelta(days=1)
    return end_time - start_time

def calculate_hours_worked(start, lunch_start, lunch_end, end):
    total_worked = time_difference(start, end)
    lunch_break = time_difference(lunch_start, lunch_end)
    actual_worked = total_worked - lunch_break
    remaining_to_8_hours = timedelta(hours=8) - actual_worked
    # If remaining time is negative, no additional time is needed
    if remaining_to_8_hours.total_seconds() < 0:
        remaining_to_8_hours = timedelta(0)
    return actual_worked, remaining_to_8_hours

# Example usage:
start_time = input("Enter start time (HH:MM AM/PM): ")
lunch_start_time = input("Enter lunch start time (HH:MM AM/PM): ")
lunch_end_time = input("Enter lunch end time (HH:MM AM/PM): ")
end_time = input("Enter end time (HH:MM AM/PM): ")

hours_worked, time_to_8_hours = calculate_hours_worked(start_time, lunch_start_time, lunch_end_time, end_time)

print(f"Total Hours Worked (excluding lunch): {hours_worked}")
print(f"Time to Reach 8 Hours: {time_to_8_hours}")
