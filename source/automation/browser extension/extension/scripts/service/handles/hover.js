/**
 * 鼠标悬浮在元素上的时候高亮元素
 */
const hover = {
    run: async (data) => {
        console.log("service", "hover", data);

        // 获取当前打开的tab
        const [tab] = await chrome.tabs.query({ active: true });
        console.log("service", "hover", "tab", [tab]);
        console.log("service", "hover", "tab", tab.id);

        // 消息发送给页面
        const response = await chrome.tabs.sendMessage(tab.id, data);
        console.log("service", "hover", "response", response);
        return response;
    }
}