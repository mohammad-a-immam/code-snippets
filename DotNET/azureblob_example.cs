public ActionResult Upload(HttpPostedFileBase file)
        {
            // Create Reference to Azure Storage Account
            String storagConn = System.Configuration.ConfigurationSettings.AppSettings["StorageConnectionString"];
            CloudStorageAccount storageacc = CloudStorageAccount.Parse(storagConn);

            //Create Reference to Azure Blob
            CloudBlobClient blobClient = storageacc.CreateCloudBlobClient();

            //The next 2 lines create if not exists a container named "democontainer"
            CloudBlobContainer container = blobClient.GetContainerReference("medcypherimages");

            container.CreateIfNotExists();

            //The next 7 lines upload the file test.txt with the name DemoBlob on the container "democontainer"
            string fileName = file.FileName;
            CloudBlockBlob blockBlob = container.GetBlockBlobReference(fileName);
            using (var filestream = file.InputStream)
            {

                blockBlob.UploadFromStream(filestream);

            }

            var imgurl = "https://medcypherstorage.blob.core.windows.net/medcypherimages/" + fileName;
            string tags = "";

            try
            {
                var visionSuggestions = GoogleVisionTest(imgurl);

                for (int i = 0; i < visionSuggestions.Count; i++)
                {
                    //TODO:: Do a if thingy to takeout comma at the end
                    tags += visionSuggestions.ElementAt(i) + ",";
                }
            }
            catch (Exception e)
            {
                tags = "";
            }

            // var model = new DataModel();
            // model.ImageUri = imgurl;
            // model.Tags = tags;
            return RedirectToAction("Tools", "Admin", new { ImageUri = imgurl, Tags = tags });
        }
