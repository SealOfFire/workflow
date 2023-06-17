/**
 * 获取鼠标位置上的元素
 */
const fromPoint = {
    run: async (data) => {
        console.log("service", "fromPoint", data);

        // 获取当前打开的tab
        const [tab] = await chrome.tabs.query({ active: true });
        console.log("service", "fromPoint", "tab", [tab]);
        console.log("service", "fromPoint", "tab", tab.id);

        // 消息发送给页面
        const response = await chrome.tabs.sendMessage(tab.id, data);
        console.log("service", "fromPoint", "response", response);
        return response;
    }
}