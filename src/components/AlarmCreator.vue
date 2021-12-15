<template>
  <div class="alarm-creator">
    <h2>Create Alarm</h2>
    <label>Datetime</label>
    <input type="datetime-local" v-model="publish.payload.datetime">
    <label>Message</label>
    <input type="text" v-model="publish.payload.message">
    <button @click="createConnection">Connect</button>
    <button @click="doPublish">Create</button>
  </div>
</template>

<script>
import mqtt from 'mqtt'

export default {
  data() {
    return {
      connection: {
        host: '192.168.43.245',
        port: 8083,
        endpoint: '/mqtt',
        clean: true, 
        connectTimeout: 4000, 
        reconnectPeriod: 4000, 
        clientId: 'mqttjs_3be2c321',
        username: 'emqx_test',
        password: 'emqx_test',
      },
      publish: {
        topic: 'watch/setAlarm',
        qos: 0,
        payload: {
          datetime: new Date().toLocaleString('en-GB'),
          message: 'asd',
        },
      },
      receiveNews: '',
      qosList: [
        { label: 0, value: 0 },
        { label: 1, value: 1 },
        { label: 2, value: 2 },
      ],
      client: {
        connected: false,
      },
      subscribeSuccess: false,
    }
  },
  methods: {
    createConnection() {
      const { host, port, endpoint, ...options } = this.connection
      const connectUrl = `mqtt://${host}:${port}${endpoint}`
      try {
        this.client = mqtt.connect(connectUrl, options)
      } catch (error) {
        console.log('mqtt.connect error', error)
      }
      this.client.on('connect', () => {
        console.log('Connection succeeded!')
      })
      this.client.on('error', error => {
        console.log('Connection failed', error)
      })
    },
    doPublish() {
      const { topic, qos, payload } = this.publish
      this.client.publish(topic, JSON.stringify(payload), qos, error => {
        if (error) {
          console.log('Publish error', error)
        }
      })
    },
  },
}
</script>

<style scoped>
.alarm-creator {
  margin: 1em auto;
  background: var(--yellow-light);
  max-width: 360px;
  display: flex;
  flex-direction: column;
  border-radius: 8px;
}

label {
  text-align: left;
  margin: 0 1em;
}

input {
  margin: 1em auto;
  width: 90%;
}

button:active {
  background: var(--red-light);
}

button {
  margin: 1em auto;
  padding: 0.5em;
  width: 95%;
  border: none;
  border-radius: 5px;
  background: var(--red-dark);
  color: white;
}

</style>
