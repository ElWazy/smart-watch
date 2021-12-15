<template>
  <h1>Smart Alarm</h1>
  <Watch />
  <AlarmCreator />
</template>

<script>
import Watch from './components/Watch.vue'
import AlarmCreator from './components/AlarmCreator.vue'

export default {
  name: 'App',
  components: {
    Watch,
    AlarmCreator,
  }
}
</script>

<style>
:root {
  --cyan-light: #96ceb4;
  --cream-light: #ffeead;
  --yellow-light: #ffcc5c;
  --red-light: #ff6f69;

  --cyan-dark: #588c7e;
  --cream-dark: #f2e394;
  --yellow-dark: #f2ae72;
  --red-dark: #d96459;

  --fore: #2c3e50;
}
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: var(--fore);
  margin-top: 60px;
}
</style>
