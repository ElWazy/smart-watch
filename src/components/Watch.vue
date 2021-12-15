<template>
  <div class="timer">
    <h2>{{ time }}</h2>
    <h4>{{ date }}</h4>
  </div>
</template>

<script>
import mqtt from 'mqtt'

export default {
  data() {
    return {
      time: '00:00:00',
      date: '2000/01/01',
      connection: {
        host: '192.168.43.245',
        port: 8083,
        endpoint: '/mqtt',
        clean: true, 
        connectTimeout: 4000, 
        reconnectPeriod: 4000, 
        clientId: 'watcher',
        username: 'waasd',
        password: 'asdw',
      },
      subscription: {
        topic: 'watch/datetime',
        qos: 0,
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
      this.client.on('message', (topic, message) => {
        console.log(`Received message ${message} from topic ${topic}`)
        const info = JSON.parse(message)
        this.time = info.time
        this.date = info.date
      })
    },
    doSubscribe() {
      const { topic, qos } = this.subscription
      this.client.subscribe(topic, { qos }, (error, res) => {
        if (error) {
        console.log('Subscribe to topics error', error)
        return
        }
        this.subscribeSuccess = true
        console.log('Subscribe to topics res', res)
      })
    },
  },
  mounted() {
    this.createConnection()
    this.doSubscribe()
  }
}
</script>

<style scoped>
.timer {
  margin: 1em auto;
  background: var(--cyan-light);
  max-width: 360px;
  display: flex;
  flex-direction: column;
  border-radius: 8px;
}

h2 {
  margin: 0;
  padding: 0;
  font-size: 3em;
}

h4 {
  margin: 0;
  padding: 0;
  font-size: 2rem;
}
</style>
