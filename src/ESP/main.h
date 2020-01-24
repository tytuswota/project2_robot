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
    grid-column-start: 1;
    grid-column-end: 1;
    grid-row-start: 3;
    grid-row-end: 3;
  }
  
  .right
  {
    grid-column-start: 3;
    grid-column-end: 3;
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
  var control = false;
  $(document).ready(function(){
    
    function postDir(d){
      $.post( "/controller", {direction: d})
        .done(function(data){
          console.log("1");
          });}
    
    function postStop(){
      $.post( "/controller", {direction: 9})
        .done(function(data){
          console.log("1");
          });}
    
    $('.manual').on('mousedown', function() {
      if(control){
        $('.manual').css("background-color", "#800D2F");
      }else{
       $('.manual').css("background-color", "green");
      }
      control = !control;
      postDir(5);
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.forward').on('mousedown', function() {
      postDir(1);
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.back').on('mousedown', function() {
      postDir(2);
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.right').on('mousedown', function() {
      postDir(3);
    }).on('mouseup', function() {
      postStop();
      clearTimeout(timeoutId);
    });

    $('.left').on('mousedown', function() {
      postDir(4);
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
