# HTTPWebServer
A very basic HTTP Web Server that can serve html, css, js and php files.

Entrypoint is index.php for this server, i.e the file to be served at base url.

## How to build
Create a folder build then use cmake to build it.
use option `-DUSE_PHP_FPM=ON` to use fast cgi.

All commands to compile and run
```
mkdir build
cd build/
cmake .. -DUSE_PHP_FPM=ON/OFF
make
```

then create input.txt and output.txt in the folder with the output i.e
```
cd bin
touch input.txt
touch output.txt
```

Now add whatever supported files you want along with index.php and run it.
It'll run at: localhost:8080

## Requirements
Make sure to install php, php-fpm and fast cgi

`php-cgi` and `cgi-fcgi` should be executables.

### Note
When using PHP_FPM you may want to use `sudo` so that the server can comunicate with fpm without
getting access denied.

