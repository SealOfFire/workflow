console.log("content");
//importScripts('handles/commands.js')

/** 
 * 接收插件发送的数据
 */
chrome.runtime.onMessage.addListener(
    (request, sender, sendResponse) => {
        console.log("content", "onMessage", request, sender, sendResponse);
        console.log("content", "onMessage", "request", request);
        console.log("content", "onMessage", "request", request.Success);
        //const response = commands[data.ommand](data);
        //const result = commands[request.Command](request);
        //request.Success = true;
        const response = commands[request.Command](request);

        sendResponse(response);
    }
);