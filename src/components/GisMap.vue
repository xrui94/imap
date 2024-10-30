<script setup lang="ts">
import {
    // defineProps, // 是一个编译宏，不再需要显示地导入进来
    ref,
    onBeforeUnmount,
    onMounted,
} from "vue";

import { from, /*Observable*/ } from "rxjs";
import { share  } from "rxjs/operators";

interface LibConfig {
    js: String,
    css: String
}

interface MapInitOptions {
    cesium: LibConfig,
    proj4: String,
    engine: LibConfig
}

const props = defineProps({
    id: {
        type: String,
        required: true,
        validator: function (value: String) {
            const res = value.length > 0;
            !res && console.error('The length of prop "id" must be greater than 0.');
            return res;
        }
    },
    options: {
        type: Object,
        required: true,
        validator: function (value: MapInitOptions) {
            // let res = false
            if (value?.cesium.js?.length > 0 &&
                value?.cesium.css?.length > 0 &&
                value?.proj4?.length > 0 &&
                value?.engine.js?.length > 0 &&
                value?.engine.css?.length > 0
            ) {
                return true
            } else {
                console.error('The length of prop "id" must be greater than 0.');
                return false
            }
        }
    },
})

let mapContainer = ref("");
(window as any).map = undefined;
let creatorPromise:any = undefined

// 加载cesium脚本
function loadLibrary(): undefined | Promise<any> {
    if ((window as any).Cesium) {
        return;
    }
    return new Promise((resolve, _) => {
        Promise.all([
            importCesiumJs(),
            importCesiumCss(),
            importProj4Js(),
            importEngineCss()
        ]).then(() => {
            importEngineJs().then(() => {
                // (window as any).Cesium = res[0];
                // 这一行不能少，否则（由于是ts，因此，参数不能为空，传递一个undefined），
                // 将导致onMounted生命周期函数中，处于回调函数中的init函数调用无法被执行
                resolve(undefined);
            });
        });
    });
}

function importCesiumJs() {
    const cesiumUrl = props.options.cesium.js;
    const scriptEl = document.createElement("script");
    scriptEl.src = cesiumUrl;
    document.body.appendChild(scriptEl);
    return new Promise((resolve, reject) => {
        scriptEl.onload = () => {
            if ((window as any).Cesium) {
                resolve((window as any).Cesium);
            } else {
                reject(new Error("加载Cesium.js时，发生错误！"));
            }
        };
    });
}

function importCesiumCss() {
    const cesiumCssUrl = props.options.cesium.css;
    const linkEl = document.createElement("link");
    linkEl.type = "text/" + "css";
    linkEl.rel = "stylesheet";
    linkEl.href = cesiumCssUrl;
    document.body.appendChild(linkEl);
    return new Promise((resolve, _) => {
        linkEl.onload = () => {
            resolve(linkEl);
        };
    });
}

function importProj4Js() {
    const proj4Url = props.options.proj4;
    const scriptEl = document.createElement("script");
    scriptEl.src = proj4Url;
    document.body.appendChild(scriptEl);
    return new Promise((resolve, reject) => {
        scriptEl.onload = () => {
            if ((window as any).proj4) {
                resolve((window as any).proj4);
            } else {
                reject(new Error("加载proj4.js时，发生错误！"));
            }
        };
    });
}

function importEngineJs() {
    const engineUrl = props.options.engine.js;
    const scriptEl = document.createElement("script");
    scriptEl.src = engineUrl;
    scriptEl.type = "module";
    document.body.appendChild(scriptEl);
    return new Promise((resolve, reject) => {
        scriptEl.onload = () => {
            if ((window as any).REngine) {
                resolve((window as any).REngine);
            } else {
                reject(new Error("加载REngine.js时，发生错误！"));
            }
        };
    });
}

function importEngineCss() {
    const engineCssUrl = props.options.engine.css;
    const linkEl = document.createElement("link");
    linkEl.type = "text/" + "css";
    linkEl.rel = "stylesheet";
    linkEl.href = engineCssUrl;
    document.body.appendChild(linkEl);
    return new Promise((resolve, _) => {
        linkEl.onload = () => {
            resolve(linkEl);
        };
    });
}

async function init() {
    if (!(window as any).REngine) {
        throw new Error('错误：无法从window上获取REngine对象！');
    }

    // 创建REngine.Map实例
    const map = new (window as any).REngine.Map(mapContainer.value, {});

    // 通过REngine管理map对象，防止页面中有多个map实例时，
    // 先创建的REngine.Map类实例被后创建的实例覆盖
    (window as any).REngine.setMap(props.id, map);
    
    // 发送事件
    // 注：Vue2中，不建议使用此处传递出去的
    // map对象，主要是避免双向绑定，造成卡顿，
    // 应使用REngine.getMap方法获取。Vue3中
    // 则建议使用此处传递出去的map对象
    // Vue3中也许可以
    // this.$emit("ready", map);
}

onMounted(async () => {
    // 使用rxjs的多播，解决Cesium.js重复挂载的问题
    if ((window as any).Cesium) {
        init()
    } else {
        if (creatorPromise === undefined) {
            const libPromise = loadLibrary()
            if (libPromise !== undefined) {
                creatorPromise = from(libPromise).pipe(share())
            }

            // 使用纯JS中的Promise语法
            // creatorPromise = loadLibrary()
        }

        // 使用rxjs来处理
        creatorPromise.subscribe(() => {
            init()
        });

        // 使用纯JS中的Promise语法
        // creatorPromise.then(() => {
        //     init()
        // })
        // .catch((error: String) => {
        //     console.error(error)
        // })
    }
})

onBeforeUnmount(() => {
    (window as any).REngine.clearMap()
})

// Vue2和Vue3生命周期函数对比
// vue2           ------->      vue3
 
// beforeCreate   -------->      setup(()=>{})
// created        -------->      setup(()=>{})
// beforeMount    -------->      onBeforeMount(()=>{})
// mounted        -------->      onMounted(()=>{})
// beforeUpdate   -------->      onBeforeUpdate(()=>{})
// updated        -------->      onUpdated(()=>{})
// beforeDestroy  -------->      onBeforeUnmount(()=>{})
// destroyed      -------->      onUnmounted(()=>{})
// activated      -------->      onActivated(()=>{})
// deactivated    -------->      onDeactivated(()=>{})
// errorCaptured  -------->      onErrorCaptured(()=>{})
</script>

<template>
    <div ref="mapContainer" id="map-container"></div>
</template>

<style scoped>
#map-container {
    width: 100%;
    height: 100%;
    margin: 0;
    padding: 0;
}
</style>