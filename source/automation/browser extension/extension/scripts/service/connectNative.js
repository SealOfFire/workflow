/**
 * 处理插件和本地程序通信
 */
const connectNative = {
    // 和本地应用通信的对象
    port: null,

    /**
     * 和本地应用建立连接
     */
    connectNative: (application) => {
        console.log("connectNative", "connectNative", application);
        this.port = chrome.runtime.connectNative(application);

        console.log("connectNative", "port", port);

        // 接收数据的回调
        //this.port.onMessage.addListener(this.received);
        this.port.onMessage.addListener((response) => {
            console.log("connectNative", "received", response);
            //console.log("connectNative", "received: ", this.receivedCallback);
            if (this.receivedCallback) {
                result = this.receivedCallback(response);
                console.log("connectNative", "result", result);
                if (result && Object.prototype.toString.call(result) === '[object Promise]') {
                    // 返回值是Promise类型的时候，从回调中获取返回值
                    console.log("connectNative", "Promise ");
                    result.then(
                        (value) => {
                            console.log("connectNative", "result", value);
                            this.port.postMessage(value);
                        }
                    );
                }
                else {
                    console.log("connectNative", "not Promise ");
                    this.port.postMessage(result);
                }
            }
        });

        // 断开连接的回调
        this.port.onDisconnect.addListener(function () {
            console.log('Disconnected');
        });
    },

    /**
     * 接收到数据后的回调
     */
    receivedCallback: null,

    /**
     * 数据发送给本地应用
     */
    /*
    send: (data) => {
        this.port.postMessage(data);
    },
    */
    /**
     * 从本地应用接收数据
     */
    /*
    received: (response) => {
        console.log("connectNative", "received: ", response);
        this.receivedCallback(response);
    },
    */

    /**
     * 测试
     */
    test: () => {
        console.log("connectNative", "test");
    },

    /**
     * 断开连接
     */
    disconnect: () => {
        this.port.disconnect();
    }
}