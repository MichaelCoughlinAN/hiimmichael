# Michael Coughlin
# hiimmichael.com
# 2019

import aws_api as aws
import boto3
from datetime import datetime


def main():
    test_table = 'Test'
    test_column_name = 'Id'
    test_column_value = 'test'

    print('Starting AWS DynamoDB Script\n')

    # Test inserting data into database
    if aws.insert_into_table(test_table, {test_column_name : test_column_value, 'Id' : '1'}):
        print('Insert successful')
    else:
        print('Insert failed')

    print('')

    # Test reading an item from the database
    print(aws.read_item_from_table(test_table, test_column_name,  test_column_value))

    print('')

    # Test querying the table of the database for a value
    print(aws.query_table(test_table, test_column_name, test_column_value))

    print('')

    # Test scanning the table of the database for a value
    print(aws.scan_table(test_table, test_column_name, test_column_value))

    print('')

    # Full scan of all pages in the table of the database for a value
    print(aws.scan_table_allpages(test_table, test_column_name, test_column_value))

    print('')

    # Get some meta-data about a specific table
    print (aws.get_table_metadata(test_table))

    print('')

    # Update a table item's values
    if aws.update_table_item(test_table, {test_column_name :  test_column_value}, {'Id' : '5', 'uhhh' : 'yes'}) :
        print('Update Successful')
    else:
        print('Update Failed')

    print('')

    # Test getting the count of a table in the database
    print (aws.get_table_size(test_table))

    print('')

    # Print all tables in the database
    print(aws.list_all_tables_in_database())

    print('')

    # Create a backup of the table
    backup_details = aws.create_table_backup(test_table, test_table + '_backup')
    print(backup_details)
    backup_details = backup_details['BackupDetails']
    print(backup_details['BackupArn'])

    print('')

    # List all backups that exists of a table in the database
    print(aws.list_all_backups(test_table, datetime(2018, 1, 1), datetime(2019, 1, 1), 100))

    print('')

    print(aws.delete_table_backup(backup_details['BackupArn']))

    print('')

    # Test removing an item from a table in the database
    if aws.remove_from_table(test_table, test_column_name,  test_column_value):
        print('Remove successful')
    else:
        print('Remove failed')


if __name__ == "__main__":
    main()
