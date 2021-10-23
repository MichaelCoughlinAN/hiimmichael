# Michael Coughlin
# hiimmichael.com
# 2019

import boto3
from boto3.dynamodb.conditions import Key


# Toggle Print Statements
DEBUG = True

# Access keys will be moved to config file in production
dynamodb = boto3.resource('dynamodb',
                          aws_access_key_id='',
                          aws_secret_access_key='',
                          region_name='us-east-2')

client = boto3.client('dynamodb',
                      aws_access_key_id='',
                      aws_secret_access_key='',
                      region_name='')


######################################################################################################
###################################### BOTO3 Resource Functions ######################################
######################################################################################################

# Insert item into DynamoDB table
# If item already exists, item is replaced with new item
# Params:
#   table_name : The name of the table to insert into
#   item : The item to insert into the table
def insert_into_table(table_name, item):
    if DEBUG:
        print('Inserting into table ' + table_name)

    table = dynamodb.Table(table_name)
    response = table.put_item(Item=item)

    if response['ResponseMetadata']['HTTPStatusCode'] == 200:
        return True
    else:
        return False


# Remove item from DynamoDB table
# Params:
#   table_name : The name of the table to insert into
#   key_name : The column name of the table
#   key_value : The value of the key entry
def remove_from_table(table_name, key_name, key_value):
    if DEBUG:
        print('Removing from table ' + table_name)

    table = dynamodb.Table(table_name)

    response = table.delete_item(Key={key_name: key_value})

    if response['ResponseMetadata']['HTTPStatusCode'] == 200:
        return True
    else:
        return False


# Get item from DynamoDB table
# Params:
#   table_name : The name of the table to insert into
#   key_name : The column name of the table
#   key_value : The value of the key entry
def read_item_from_table(table_name, key_name, key_value):
    if DEBUG:
        print('Getting item from table ' + table_name)

    table = dynamodb.Table(table_name)
    response = table.get_item(Key={key_name : key_value})

    return response


# Perform a query operation on the table
# Can specify filter_key (col name) and its value to be filtered
# Params:
#   table_name : The name of the table to insert into
#   filter_key : The column name of the table
#   filter_value : The value of the key entry
def query_table(table_name, filter_key=None, filter_value=None):
    if DEBUG:
        print('Querying table ' + table_name + ' for value ' + filter_value)

    table = dynamodb.Table(table_name)

    if filter_key and filter_value:
        filtering_exp = Key(filter_key).eq(filter_value)
        response = table.query(KeyConditionExpression=filtering_exp)
    else:
        response = table.query()

    return response


# Perform a scan operation on table
# Can specify filter_key (col name) and its value to be filtered
# Results in a DynamoDB table are paginated. Scan it is not guaranteed to grab all the data in table
# See scan_table_allpages
# Params:
#   table_name : The name of the table to insert into
#   filter_key : The column name of the table
#   filter_value : The value of the key entry
def scan_table(table_name, filter_key=None, filter_value=None):
    if DEBUG:
        print('Scanning table ' + table_name + ' for filter_value ' + filter_value)

    table = dynamodb.Table(table_name)

    if filter_key and filter_value:
        filtering_exp = Key(filter_key).eq(filter_value)
        response = table.scan(FilterExpression=filtering_exp)
    else:
        response = table.scan()

    return response


# Perform a scan operation on table.
# Can specify filter_key (col name) and its value to be filtered.
# This gets all pages of results. Returns list of items.
# Params:
#   table_name : The name of the table to insert into
#   filter_key : The column name of the table
#   filter_value : The value of the key entry
def scan_table_allpages(table_name, filter_key=None, filter_value=None):
    if DEBUG:
        print('Scanning all table pages ' + table_name + ' for filter_value ' + filter_value)

    table = dynamodb.Table(table_name)

    if filter_key and filter_value:
        filtering_exp = Key(filter_key).eq(filter_value)
        response = table.scan(FilterExpression=filtering_exp)
    else:
        response = table.scan()

    items = response['Items']
    while True:
        if response.get('LastEvaluatedKey'):
            response = table.scan(ExclusiveStartKey=response['LastEvaluatedKey'])
            items += response['Items']
        else:
            break

    return items


# Returns table meta-data
# Params:
#   table_name : The name of the table to gather meta-data about
def get_table_metadata(table_name):
    if DEBUG:
        print('Gathering meta-data about table ' + table_name)

    table = dynamodb.Table(table_name)

    return {
        'item_count': table.item_count,
        'primary_key_name': table.key_schema[0],
        'status': table.table_status,
        'bytes_size': table.table_size_bytes,
        'global_secondary_indices': table.global_secondary_indexes
    }


# Update attributes of the item in the table
# If item does not exist, create it
# Params:
#   table_name : The name of the table
#   primary_key_dict : Dictionary{primary key : key value} Update where primary key is equal to key value
#   key_value_dict : Dictionary{col 1 : new col 1 value, col 2 : new column 2 val}
#                    Update columns with new column values
# primary_key_dict helps us locate the data row in the database table, key_value_dict contains the values to update
# the corresponding columns in the data row
def update_table_item(table_name, primary_key_dict, key_value_dict):
    if DEBUG:
        print('Updating table ' + table_name + ' where ' + list(primary_key_dict.keys())[0] + ' is equal to ' + list(primary_key_dict.values())[0])

    table = dynamodb.Table(table_name)

    # update_table_expression_tuple[0] : UpdateExpression
    # update_table_expression_tuple[1] : ExpressionAttributeValues
    update_table_expression_tuple = update_table_item_helper(key_value_dict)

    response = table.update_item(
        Key=primary_key_dict,
        UpdateExpression=update_table_expression_tuple[0],
        ExpressionAttributeValues=update_table_expression_tuple[1]
    )

    if response['ResponseMetadata']['HTTPStatusCode'] == 200:
        return True
    else:
        return False


# Helper function to update_table_item method
# DynamoDB requires an expression string to be passed as a parameter as well as a dictionary of expression attributes
# UpdateExpression Syntax: 'SET col1 = :val1, col2 - :val2, ...
# ExpressionAttributeValues: {:val1 :  new_value, :val2: new_value, ...
# See https://boto3.readthedocs.io/en/latest/reference/services/dynamodb.html#DynamoDB.Client.update_item
def update_table_item_helper(key_value_dict):
    update_expression_str = 'SET '
    expression_attribute_dict = {}

    length = len(key_value_dict)
    count = 1

    # Python2 use key_value_dict.iteritems()
    for key, value in key_value_dict.items():
        update_expression_str += key + ' = :val' + str(count)

        if length != 1 and count != length:
                update_expression_str += ', '

        expression_attribute_dict[':val' + str(count)] = value

        count = count + 1

    return update_expression_str, expression_attribute_dict


######################################################################################################
####################################### BOTO3 Client Functions #######################################
######################################################################################################


# Get the number of entries in a given table
def get_table_size(table_name):
    if DEBUG:
        print('Calculating size of table ' + table_name)

    table = dynamodb.Table(table_name)
    return table.item_count


# List all the existing tables in the database
def list_all_tables_in_database():
    if DEBUG:
        print('Listing all tables in database')

    return client.list_tables()


# List all backup points that exist for a table
# Params:
#   table_name : The name of the table
#   datetime_lower_bound : The starting date to being searching for backups
#   datetime_upper_bound : The ending date to stop searching for backups
#   max_size_of_list_returned : The max amount of backups returned
def list_all_backups(table_name, datetime_lower_bound, datetime_upper_bound, max_size_of_list_returned):
    if DEBUG:
        print('Listing all backups for table ' + table_name)

    response = client.list_backups(
        TableName=table_name,
        Limit=max_size_of_list_returned,
        TimeRangeLowerBound=datetime_lower_bound,
        TimeRangeUpperBound=datetime_upper_bound,
    )

    return response


# Create a backup of the table
# Params:
#   table_name : The name of the table
#   table_backup_name : The name of the table backup
def create_table_backup(table_name, table_backup_name):
    if DEBUG:
        print('Creating backup of table ' + table_name)

    response = client.create_backup(
        TableName=table_name,
        BackupName=table_backup_name
    )

    return response


# Delete a backup associated with a table
# Params:
#   backup_arn : The BackupARN associated with the backup
def delete_table_backup(backup_arn):
    if DEBUG:
        print('Removing table backup ' + backup_arn)

    response = client.delete_backup(
        BackupArn=backup_arn
    )

    return response


# Restore a database table to a database backup
# This creates a new table if it does not exist
# Params:
#   table_name : The name of the table to backup
#   backup_arn : The BackupARN associated with the backup
def restore_from_table_backup(table_name, backup_arn):
    if DEBUG:
        print('Restoring table from backup ' + backup_arn)

    response = client.restore_table_from_backup(
        TargetTableName=table_name,
        BackupArn=backup_arn
    )

    return response
