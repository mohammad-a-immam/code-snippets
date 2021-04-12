import $ from "jquery";

$.ajax({
    url: ("identity/signup"),
    type: 'post',
    data: { name: "university" },
    success: (data)=> {
        //success function
    },
    error: (error) => {console.log("oops"); //fail function
    }
});