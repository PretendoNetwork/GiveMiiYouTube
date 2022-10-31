# GiveMiiYouTube
Since October 27, 2022 the YouTube app for the Wii U has been discontinued and the app can no longer be accessed.  
To check if the service is available the YouTube app requests a service token from `https://account.nintendo.net/v1/api/provider/service_token/` with a YouTube specific client id.  
This endpoint now responds with:
```html
<errors>
    <error>
        <code>0123</code>
        <message>Service has expired</message>
    </error>
</errors>
```
The app then checks if acquiring this token has been sucessful and if not it will display the error. The acquired token itself is not used.  
This is a Wii U Plugin System plugin for Aroma which just makes this request always return sucess and thus allowing the YouTube app to continue functioning.

## Info about version 2.0
On November 1st, 2022 YouTube started returning response 404 for the `WiiU` useragent platform.  
Since v2.0 this plugin patches the platform in the useragent for the YouTube app to `NoU` instead of `WiiU`, which bypasses this block.

## Special Thanks to
[@ashquarky](https://github.com/ashquarky) for the awesome patcher framework which was taken from [Nimble](https://github.com/PretendoNetwork/Nimble).

## Building
```bash
# Build docker image (only needed once)
docker build . -t givemiiyoutube_builder

# make 
docker run -it --rm -v ${PWD}:/project givemiiyoutube_builder make

# make clean
docker run -it --rm -v ${PWD}:/project givemiiyoutube_builder make clean
```
