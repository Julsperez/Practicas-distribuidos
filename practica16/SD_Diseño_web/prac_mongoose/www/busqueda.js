$("#search-res").hide();
$('#form-search').submit(function(){
    $("#search-res").show();
    $("#search-res").html("<img src='load.gif' width=50/>");
    $.ajax({
        type: "POST",
        url: "/search",
        data:{
            query:$("#search").val()
        },
        success: function(data){
            $("#search-res").html(data);
        }
    });
    return false;
});