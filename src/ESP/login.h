#include <Esp.h>
const char LOGIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<HEAD>
<link rel="stylesheet" href="https://unpkg.com/picnic">
<style>
</style>
  
</HEAD>
<BODY>
  <div class="formWarpper">
    <form action="/login" method="POST">
      <input type="text" name="username" placeholder="Username"></br>
      <input type="password"  name="password" placeholder="Password"></br>
      <input class="loginSUB" type="submit" value="Login">
    </form>
  </div>
</BODY>
)=====";