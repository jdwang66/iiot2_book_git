$(function(){
	$("#sum").click(function(){
		console.log("button click");
		var n1 = $("#num1").val();
		var n2 = $("#num2").val();
		var API="http://localhost:1880/test/sum";
		$.post(API,{num1:n1, num2:n2}, function(res){
			$("#result").text(res.mySum);
		});
	});
	
	$("#sub").click(function(){		
		var n1 = $("#num1").val();
		var n2 = $("#num2").val();
		var API="http://localhost:1880/test/sub?num1="+n1+"&num2="+n2;
		$.get(API, function(res){
			$("#result").text(res.mySub);
		});
	});

	$("#mul").click(function(){		
		var n1 = $("#num1").val();
		var n2 = $("#num2").val();
		var API="http://localhost:1880/test/mul/"+n1+"/"+n2;
		$.get(API, function(res){
			$("#result").text(res.myMul);
		});
	});
});
