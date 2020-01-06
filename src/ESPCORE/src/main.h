#include <Esp.h>
const char CONTROLLER_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<HEAD>
<link rel="stylesheet" href="https://unpkg.com/picnic">
<script
  src="https://code.jquery.com/jquery-3.4.1.min.js"
  integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
  crossorigin="anonymous"></script>
<script>
  $(document).ready(function(){
    //alert("test");
    $(".manual").click(function(){
      $.post( "/controller", {direction:"man"})
        .done(function(data){
          console.log("1");
      });

    $(".forward").click(function(){
      $.post( "/controller", {direction:"forward"})
        .done(function(data){
          console.log("1");
      });

    });  

    $(".back").click(function(){
      $.post( "/controller", {direction:"back"})
        .done(function(data){
          console.log("1");
      });
    });
    
    $(".right").click(function(){
      $.post( "/controller", {direction:"right"})
        .done(function(data){
          console.log("1");
      });
    });

    $(".left").click(function(){
      $.post( "/controller", {direction:"left"})
        .done(function(data){
          console.log("1");
      });
    });
    
  });

</script>

<style>

</style>
  
</HEAD>
<BODY>
  <button class="manual">manual</button><br/>
  <button class="forward">forward</button><br/>
  <button class="back">back</button><br/>
  <button class="right">right</button><br/>
  <button class="left">left</button><br/>
</BODY>
)=====";