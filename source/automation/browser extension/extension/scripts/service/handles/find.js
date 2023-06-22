/**
 * 通过元素属性查找元素
 */
const find = {
    run: async (data) => {
        console.log("service", "find", data);

        // 获取当前打开的tab
        const [tab] = await chrome.tabs.query({ active: true });
        console.log("service", "find", "tab", [tab]);
        console.log("service", "find", "tab", tab.id);

        // 消息发送给页面
        const response = await chrome.tabs.sendMessage(tab.id, data);
        console.log("service", "find", "response", response);
        return response;
    }
}