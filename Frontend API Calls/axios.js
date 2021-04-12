//import the axios


//call .net get backend method
axios.get(`identity/signup`,
    {
        params: {
            parametername: 'value',
            moreparametername: 'value'
        }
    })
    .then(function (response) {
    }).catch((e) => {
    console.log(e);
})


