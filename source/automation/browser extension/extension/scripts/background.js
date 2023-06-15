console.log("插件启动")

/*
 * 启动，连接 ping_pong 原生应用
 */
var port = chrome.runtime.connectNative("com.my_company.my_application");

/*
 * 监听从原生应用发来的消息
 */
port.onMessage.addListener((response) => {
    console.log("Received: " + response);
    console.log(response);
    port.postMessage({ text: 'Hello, my_application2' });
});

port.onDisconnect.addListener(function () {
    console.log('Disconnected');
});


commands = {
    "newtab": import("./handles/newTab")
}

/**
 * 执行命令
 */
function executeCommand(value) {
    console.log('executeCommand', value);
    commands[value.commands](value);
}

function newTab(url) {
    chrome.tabs.create({ url: "https://www.baidu.com" })
}