# HTTPWebServer
A very basic HTTP Web Server that can serve html, css, js and php files.

Entrypoint is index.php for this server, i.e the file to be served at base url.

## How to build
To build you can use `scripts/buid.sh` script to create a clean build.

It will create a build folder(remove build folder if present), compile the program,
copy files from `public/` folder to `build/bin/` and run it. 

These are test files feel free to replace them, but don't remove `input.txt` and `output.txt`.

```
cd scripts/
chmod +x build.sh
./build.sh
```

If you want to enable php fpm, use
```
./build.sh -DUSE_PHP_FPM=ON
```

If you make some changes on code and want to rebuild
```
./rebuild.sh
```
OR
```
./rebuild.sh -DUSE_PHP_FPM=ON
```

and if you just want to run it again
```
./run.sh
```
OR
```
cd build/bin/
./HTTPWebServer
```

Now add/replace whatever supported files you want to.

It'll run at: localhost:8080

## Requirements
Make sure to install php, php-fpm and fast cgi

`php-cgi` and `cgi-fcgi` should be executables.

### Note
When using PHP_FPM you may want to use `sudo` so that the server can comunicate with fpm without
getting access denied.
