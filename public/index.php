<?php
echo "For get req: Hello " . $_GET["name"] . "<br/>";
echo "For post req: Hello " . $_POST["name"] . "<hr/>";
echo file_get_contents("index.html");
?>