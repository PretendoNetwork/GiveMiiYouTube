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

## Building

For building you need: 
- [wups](https://github.com/wiiu-env/WiiUPluginSystem)
- [wut](https://github.com/decaf-emu/wut)

Install them (in this order) according to their README's. Don't forget the dependencies of the libs itself.
