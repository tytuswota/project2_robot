#include "main.h"
const char MAIN_page[] PROGMEM = R"=====(
<HTML>
  <HEAD>
      <link rel="stylesheet" type="text/css" href="main.css">
      <TITLE>Robot page</TITLE>
      <STYLE>
        HTML{
           height: 100%;
           width: 100%;
           background-color: #CBEEF3; 
         }
         button
         {
           background-color: blue;
           color: white; 
         }
         b
         {
          color: black;
         }
         .type-1
         {
          margin-top: 500px;
         }

         body 
         {
           
           margin: 10px;
           text-align: center;
         }
      </STYLE>
  </HEAD>
<BODY>
  <CENTER>
      <B>wow</B><br/>
      <div class="type-1">
        <div>
          <a href="\socket1On" class="btn btn-1">
           <span class="txt">Turn on</span>
          <span class="round"><i class="fa fa-chevron-right"></i></span>
         </a>
        </div>
        <div>
          <a href="\socket1Off" class="btn btn-1">
           <span class="txt">Turn off</span>
          <span class="round"><i class="fa fa-chevron-right"></i></span>
         </a>
        </div>
     </div>
  </CENTER> 
</BODY>
</HTML>
)=====";
