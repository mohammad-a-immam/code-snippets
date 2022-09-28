import pymssql  # for sql server usages
SERVER = '10.0.246.102'
USER = 'osi'
PASS = 'FZT537rw'
# purpose: to connect to the provided sql server. serverName is a string referring to the configuration name
# saved in props
def ConnectToSql():
    # Preparing and Testing The SQL Connection

    # create connection to the sql server
    conn = pymssql.connect(SERVER, USER, PASS, 'hist')
    return conn.cursor()


if __name__ == '__main__':
    # TEST SQL CONNECTION
    context = ConnectToSql()
    if context.connection:
        print("success")
    else:
        print("faile")
    input("click to complete")
    context.close