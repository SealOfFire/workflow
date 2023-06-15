console.log("service-worker.js");
importScripts('connectNative.js');
importScripts('handles/commands.js')

// 和本地应用建立连接
connectNative.receivedCallback = receivedCallback;
connectNative.connectNative("com.my_company.my_application");
//connectNative.disconnect();

chrome.runtime.onStartup.addListener(
    () => {
        console.log("onStartup");
    }
)

chrome.runtime.onSuspend.addListener(
    () => {
        console.log("onSuspend");
    }
)

chrome.management.onDisabled.addListener(
    (info) => {
        console.log("management", "onDisabled", info);
        connectNative.disconnect();
    }
)

chrome.management.onEnabled.addListener(
    (info) => {
        console.log("management", "onEnabled", info);

    }
)

function receivedCallback(data) {
    console.log("service-worker", "receivedCallback1", data);
    const result = commands[data.Command](data);
    console.log("service-worker", "receivedCallback2", result);
    return result
}



