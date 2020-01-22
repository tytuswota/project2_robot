#include <Esp.h>
const char CONTROLLER_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<HEAD>
<style>
  .container {
    display: grid;
    grid-template-columns: auto auto auto;
    grid-template-rows: auto auto auto auto;
    padding: 20px;
  }
  .manual
  {
    background-color: #800D2F;
    grid-column-start: 2;
    grid-column-end: 2;
    grid-row-start: 3;
    grid-row-end: 3;
  }
  .forward
  {
    grid-column-start: 2;
    grid-column-end: 2;
    grid-row-start: 2;
    grid-row-end: 2;
  }
  
  .back
  {
    grid-column-start: 2;
    grid-column-end: 2;
    grid-row-start: 5;
    grid-row-end: 4;
  }
  
  .left
  {
    grid-column-start: 3;
    grid-column-end: 3;
    grid-row-start: 3;
    grid-row-end: 3;
  }
  
  .right
  {
    grid-column-start: 1;
    grid-column-end: 1;
    grid-row-start: 3;
    grid-row-end: 3;
  }

  .container-item {
    background-color: rgba(255, 255, 255, 0.8);
    border: 1px solid rgba(0, 0, 0, 0.8);
    padding: 20px;
    font-size: 30px;
    text-align: center;
  }
</style>
<link rel="stylesheet" href="https://unpkg.com/picnic">
<script
  src="https://code.jquery.com/jquery-3.4.1.min.js"
  integrity="sha256-CSXorXvZcTkaix6Yvo6HppcZGetbYMGWSFlBw8HfCJo="
  crossorigin="anonymous"></script>
<script>
  $(document).ready(function(){
    
    function postDir(d){
      $.post( "/controller", {direction: d})
        .done(function(data){
          console.log("1");
          });}
    
    function postStop(){
      $.post( "/controller", {direction: "stop_trans"})
        .done(function(data){
          console.log("1");
          });}
    
    $('.manual').on('mousedown', function() {
      postDir("man");
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.forward').on('mousedown', function() {
      postDir("forward");
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.back').on('mousedown', function() {
      postDir("back");
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.right').on('mousedown', function() {
      postDir("right");
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.left').on('mousedown', function() {
      postDir("left");
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });
  });

</script>  
</HEAD>
<BODY>
  <div class="container">
    <button class="manual" class="container-item">manual</button><br/>
    <button class="forward" class="container-item">forward</button>
    <button class="back" class="container-item">back</button>
    <button class="left" class="container-item">left</button>
    <button class="right" class="container-item">right</button>
  </div>
</BODY>
)=====";
