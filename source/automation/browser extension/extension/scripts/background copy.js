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


//
// ===== Window monitoring functions =====
window.addEventListener("load", OnPageLoad, false);

/**
 * 扩展安装时候的初始化操作
 */
chrome.runtime.onInstalled.addListener(() => {
    console.log("浏览器插件安装");
});

//
chrome.bookmarks.onCreate.addListener(() => {
    console.log("新建书签的时候会进入这个回调");
});

// 添加事件过滤器
const filter = {
    url: [{ urlMatches: "https://www.google.com/" }]
};

chrome.webNavigation.onComplete.addEventListener(() => {
    console.info("the user has loadded my favorite website!");
}, filter);

// 30s内没有新的事件会进入休眠状态。这里每25s触发一次事件
// 保持活性
function sleep(ms) { return new Promise(resolve => { setTimeout(resolve, ms) }); }
(async () => {
    while (true) {
        await sleep(25000);
        await chrome.storage.local.get();
    }
});
