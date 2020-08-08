$(document).ready(function(){
  $.ajax({
    method: "POST",
    url: "/search",
    data:{
      query: "Hola popo",
      noquery: ""
    },
    success: function(data){
      console.log(data);
    }
  });
})
