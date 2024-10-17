# imap

一个由“yhirose/cpp-httplib”库提供后端静态资源服务和接口服务，前端基于Cesium和Vue3，以操作系统默认的浏览器作为渲染UI界面的窗口的地图（GIS）类桌面应用软件。

- **特性**：
  - 后端使用C++库“[yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib)”，提供了一个轻量化的后端静态资源服务，以及接口服务；
  - 前端使用Vue3框架开发，默认由后端启动浏览器来作为显示整个程序UI界面的窗口

## 1. 目录结构说明

- 如下为imap项目工程的目录结构，及其说明。整体上，这只是在传统的Vue3项目上，新增了“src-cpp”目录和“CMakeLists.txt”文件。

|——imap
    |——public：静态开发资源存放目录，传统Vue3项目的public目录
    |——src：前端代码（*.ts），传统Vue3项目的src目录
    |——src-cpp：后端代码（*.cpp），基于Cpp-httplib开发的后端服务
    |——CMakeLists.txt：后端C++代码构建工具
    |——index.html：前端页面入库文件
    |——tsconfig.app.json
    |——tsconfig.json
    |——tsconfig.node.json
    |——vite.config.ts

## 2. 编译和打包

### 2.1 安装依赖

```sh
pnpm install
```

### 2.2 编译和热重载（开发环境）

```sh
pnpm dev
```

### 2.3 类型检查、编译和代码最小化（正式环境）

```sh
pnpm build
```
