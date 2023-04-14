window.onload=function(){
    
    console.log('%cAuthor:朱学聪','color:pink');
    console.error('%c此程序请勿用于商业用途，若转载，请标明作者及出处,侵权必究','color:red');
    var randomSpan=document.querySelectorAll("#wrapper .randomPic span");
    document.oncontextmenu = () => false;
    document.onkeydown=function(e){
        if(e.ctrlKey && e.key=="p"){
            e.preventDefault();
            return;
        }
        if(e.ctrlKey && e.key=="P"){
            e.preventDefault();
            return;
        }
    }
    goto();
    $(".ButtonsTogether .generateButton button").click(function(){
        goto();
    })
    $(".ButtonsTogether .shareButton button").click(function(){
        $(".getUserInput").show();
        $(".getUserInput input").val("");
    })
    $(".getUserInput .sure").click(function(){
        var paperName=$(".getUserInput input").val();
        if(paperName==""){
            alert("请输入卷名");
            return;
        }
        $(".getUserInput").hide();
        $(".testPaper span").text(paperName+"卷");
        window.print();
    })
    $(".getUserInput .notSure").click(function(){
        $(".getUserInput").hide();
    })
    function goto(){
        var pattern= new Date();
        var randomArr=[1,2,3,4,5,6,7,8,9,10,11,12,13,14]; //length==14
        var randomOne=[1,2,3,4,5,6,7,8,9,10,11,12,13,14];
        var randomID=parseInt(Math.random()*8999)+1001;
        var randomChannle=parseInt(Math.random()*8)+10;
        $(".Timer .time").text(pattern.toLocaleString());
        for(let i=0;i<17;i++){
            if(i<14){
                var rand=parseInt(Math.random()*randomOne.length);
                $(randomSpan[i]).text(randomOne[rand]);
                randomOne.splice(rand,1);
            }else{
                var rand=parseInt(Math.random()*randomArr.length);
                $(randomSpan[i]).text(randomArr[rand]);
                randomArr.splice(rand,1);
            }
        }
        $(randomSpan[17]).text(randomID);
        $("#wrapper .randomPic h4").text("通道:"+randomChannle);
    }
    
}