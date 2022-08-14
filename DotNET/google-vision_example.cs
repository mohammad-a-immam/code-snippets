 public List<String> GoogleVisionTest(string uri)
        {
            ServicePointManager.ServerCertificateValidationCallback +=
                 (sender, certificate, chain, sslPolicyErrors) => true;
            List<String> data = new List<String>();
            var endpoint = "/v1/images:annotate";
            var request = new RestRequest(endpoint, Method.POST);
            var restClient = new RestClient("https://vision.googleapis.com");

            request.AddParameter("key", "AIzaSyBWheyexJL6DdMsr-AnQxm2jJrymxhjBts", ParameterType.QueryStringWithoutEncode);
            var jsonString = "{\"requests\": [{\"image\": {\"source\": {\"imageUri\": \""+ uri +"\"}},\"features\": [{\"maxResults\": 10,\"type\": \"LABEL_DETECTION\"}]}]}";
            request.AddJsonBody(jsonString);
            var response = restClient.Execute(request, Method.POST);
            VisionResponse vresponse = JsonConvert.DeserializeObject<VisionResponse>(response.Content);
            foreach (var labelannotaion in vresponse.Responses[0].LabelAnnotations)
            {
                if (labelannotaion.Score >= 0.5)
                {
                    data.Add(labelannotaion.Description);
                }
            }
            //string test = Server.UrlDecode("testestets");
            ViewBag.testInfo = data.Count;
            return data;
        }
        
        
        
        
    public partial class VisionResponse
    {
        [JsonProperty("responses")]
        public Response[] Responses { get; set; }
    }

    public partial class Response
    {
        [JsonProperty("labelAnnotations")]
        public LabelAnnotation[] LabelAnnotations { get; set; }
    }

    public partial class LabelAnnotation
    {
        [JsonProperty("mid")]
        public string Mid { get; set; }

        [JsonProperty("description")]
        public string Description { get; set; }

        [JsonProperty("score")]
        public double Score { get; set; }

        [JsonProperty("topicality")]
        public double Topicality { get; set; }
    }
