import asyncio
from asyncua import Server, ua
import math
import numpy as np

async def main():
    # 初始化OPC UA服務器
    server = Server()
    await server.init()
    server.set_endpoint("opc.tcp://0.0.0.0:4840")

    # 註冊命名空間字串，返回命名空間索引
    uri = "http://www.iiot.com.tw"
    idx = await server.register_namespace(uri)

    # 建立地址空間
    myobj = await server.nodes.objects.add_object(idx, "MyObject")
    myvar1 = await myobj.add_variable(ua.NodeId(5, idx), "MyVariable1", 0.0)
    myvar2 = await myobj.add_variable(ua.NodeId(6, idx), "MyVarialbe2", 0.0)
    print(myvar1, myvar2)

    # 變數節點設為可寫入
    await myvar1.set_writable()
    await myvar2.set_writable()

    print("Starting server!")

    async with server:
        t = 0
        while True:
            # 生成 sin(x) 及 cos(x) 資料，將其寫入2個變數節點中
            new_val1 = np.sin(2*np.pi*t/20)
            new_val2 = np.cos(2*np.pi*t/20)
            t += 1
            print(
                f"t = {t}\t sin: {myvar1}: {new_val1:.4f}\t cos: {myvar2}: {new_val2:.4f}")
            await myvar1.write_value(new_val1)
            await myvar2.write_value(new_val2)
            await asyncio.sleep(2)

if __name__ == "__main__":
    asyncio.run(main())
