ALTER DATABASE BOSEVIKRAM SET SINGLE_USER WITH ROLLBACK IMMEDIATE    
ALTER DATABASE BOSEVIKRAM MODIFY NAME = [BOSEVIKRAM_Deleted]
ALTER DATABASE BOSEVIKRAM_Deleted SET MULTI_USER