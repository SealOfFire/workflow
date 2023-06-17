/**
 * 高亮缓存的元素
 */
const highlight = {
    run: async (data) => {
        console.log("service", "highlight", data);

        // 获取当前打开的tab
        const [tab] = await chrome.tabs.query({ active: true });
        console.log("service", "highlight", "tab", [tab]);
        console.log("service", "highlight", "tab", tab.id);

        // 消息发送给页面
        const response = await chrome.tabs.sendMessage(tab.id, data);
        console.log("service", "highlight", "response", response);
        return response;
    }
}