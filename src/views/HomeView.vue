<script setup lang="ts">
import GisMap from '../components/GisMap.vue'

import { ref } from 'vue'

const mapId = ref('home-map')
const mapOptions = ref((window as any).systemConfig)

function openFile() {
  // https://www.jianshu.com/p/646bb18d1739
  // https://blog.csdn.net/u014324940/article/details/132980242

  fetch(
    // encodeURI('http://localhost:1027/open?file=D:/xrui94/data/engine/models/osgb/西安大雁塔/DaYanTa_3DTiles1.0/tileset.json'),   // 中文字符,后端暂不支持
    encodeURI('http://localhost:1027/filepath'),
    {
      mode: 'no-cors'
    }
  )
  .then(res => {
    if (!res.ok) {
      console.error('Failed to request file.');
      return;
    }
    return res.text();
  })
  .then(res => {
    // console.log(mapId.value) 如下函数中,使用"mapId.value"时报错!!?
    (window as any).REngine.getMap('home-map').addLayer({
      type: '3DTILES',
      url: res
    })
  })
}

</script>

<template>
  <main class="main-content">
    <GisMap :id=mapId :options=mapOptions />
  </main>
  <div class="control-panel">
    <button id="open-file-btn" @click="openFile">打开</button>
  </div>
</template>

<style scoped>
.main-content {
  width: 100%;
  height: 100%;
  margin: 0;
  padding: 0;
}

.control-panel {
    position: fixed;
    top: 20px;
    right: 20px;
    min-width: 220px;

    background: #f3f8ff;
    opacity: 0.9;
    color: #000;
    overflow: hidden;
    z-index: 9999;
    position: fixed;
    padding: 8px;
    text-align: left;
    border-bottom-left-radius: 4px;
    border-bottom-right-radius: 4px;
    border-top-left-radius: 4px;
    border-top-right-radius: 4px;
}
</style>