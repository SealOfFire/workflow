/**
 * 选取元素
 */
const pickUp = {
    run: async (data) => {
        console.log("service", "pickUp", data);

        // 获取当前打开的tab
        const [tab] = await chrome.tabs.query({ active: true });
        console.log("service", "pickUp", "tab", [tab]);
        console.log("service", "pickUp", "tab", tab.id);

        // 消息发送给页面
        const response = await chrome.tabs.sendMessage(tab.id, data);
        console.log("service", "pickUp", "response", response);
        return response;
    }
}