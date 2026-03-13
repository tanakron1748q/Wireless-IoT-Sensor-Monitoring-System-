<template>
  <div class="app-container">
    <!-- Professional Header -->
    <header class="app-header">
      <div class="header-content">
        <div class="header-left">
          <div class="logo">
            <div class="logo-icon">📊</div>
            <div class="logo-text">
              <h1>Sensor Monitor</h1>
              <p>Real-time Environmental Tracking</p>
            </div>
          </div>
        </div>
        <div class="header-right">
          <div class="connection-status">
            <div :class="['status-dot', connectionStatus === 'connected' ? 'connected' : 'disconnected']"></div>
            <span>{{ connectionStatus === 'connected' ? 'Connected' : 'Disconnected' }}</span>
          </div>
          <div class="last-update">
            <svg class="clock-icon" viewBox="0 0 24 24" fill="none" stroke="currentColor">
              <circle cx="12" cy="12" r="10"></circle>
              <path d="M12 6v6l4 2"></path>
            </svg>
            <span>{{ lastUpdate }}</span>
          </div>
        </div>
      </div>
    </header>

    <!-- Main Content -->
    <main class="main-content">
      <!-- Sensor Cards Grid -->
      <div class="sensor-grid">
        <!-- Temperature Card -->
        <div class="sensor-card">
          <div class="card-header">
            <div class="card-icon temp-icon">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor">
                <path d="M14 14.76V3.5a2.5 2.5 0 0 0-5 0v11.26a4.5 4.5 0 1 0 5 0z"></path>
              </svg>
            </div>
            <div class="card-info">
              <h3>Temperature</h3>
              <span class="card-label">อุณหภูมิ</span>
            </div>
          </div>
          <div class="card-value">
            <span class="value" :style="{color: getColor('temperature', sensorData.temperature)}">
              {{ sensorData.temperature }}
            </span>
            <span class="unit">°C</span>
          </div>
          <div :class="['status-indicator', getStatusClass('temperature', sensorData.temperature)]">
            {{ getStatus('temperature', sensorData.temperature) }}
          </div>
          <div class="stats-grid">
            <div class="stat">
              <span class="stat-label">Min</span>
              <span class="stat-value">{{ stats.temperature.min }}°</span>
            </div>
            <div class="stat">
              <span class="stat-label">Max</span>
              <span class="stat-value">{{ stats.temperature.max }}°</span>
            </div>
            <div class="stat">
              <span class="stat-label">Avg</span>
              <span class="stat-value">{{ stats.temperature.avg }}°</span>
            </div>
          </div>
        </div>

        <!-- Humidity Card -->
        <div class="sensor-card">
          <div class="card-header">
            <div class="card-icon humid-icon">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor">
                <path d="M12 2.69l5.66 5.66a8 8 0 1 1-11.31 0z"></path>
              </svg>
            </div>
            <div class="card-info">
              <h3>Humidity</h3>
              <span class="card-label">ความชื้น</span>
            </div>
          </div>
          <div class="card-value">
            <span class="value" :style="{color: getColor('humidity', sensorData.humidity)}">
              {{ sensorData.humidity }}
            </span>
            <span class="unit">%</span>
          </div>
          <div :class="['status-indicator', getStatusClass('humidity', sensorData.humidity)]">
            {{ getStatus('humidity', sensorData.humidity) }}
          </div>
          <div class="stats-grid">
            <div class="stat">
              <span class="stat-label">Min</span>
              <span class="stat-value">{{ stats.humidity.min }}%</span>
            </div>
            <div class="stat">
              <span class="stat-label">Max</span>
              <span class="stat-value">{{ stats.humidity.max }}%</span>
            </div>
            <div class="stat">
              <span class="stat-label">Avg</span>
              <span class="stat-value">{{ stats.humidity.avg }}%</span>
            </div>
          </div>
        </div>

        <!-- Air Quality Card -->
        <div class="sensor-card">
          <div class="card-header">
            <div class="card-icon mq2-icon">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor">
                <path d="M17.5 19H9a7 7 0 1 1 6.71-9h1.79a4.5 4.5 0 1 1 0 9Z"></path>
              </svg>
            </div>
            <div class="card-info">
              <h3>Air Quality</h3>
              <span class="card-label">คุณภาพอากาศ</span>
            </div>
          </div>
          <div class="card-value">
            <span class="value" :style="{color: getColor('mq2', sensorData.mq2Value)}">
              {{ sensorData.mq2Value }}
            </span>
            <span class="unit">PPM</span>
          </div>
          <div :class="['status-indicator', getStatusClass('mq2', sensorData.mq2Value)]">
            {{ getStatus('mq2', sensorData.mq2Value) }}
          </div>
          <div class="stats-grid">
            <div class="stat">
              <span class="stat-label">Min</span>
              <span class="stat-value">{{ stats.mq2.min }}</span>
            </div>
            <div class="stat">
              <span class="stat-label">Max</span>
              <span class="stat-value">{{ stats.mq2.max }}</span>
            </div>
            <div class="stat">
              <span class="stat-label">Avg</span>
              <span class="stat-value">{{ stats.mq2.avg }}</span>
            </div>
          </div>
        </div>

        <!-- Distance Card -->
        <div class="sensor-card">
          <div class="card-header">
            <div class="card-icon dist-icon">
              <svg viewBox="0 0 24 24" fill="none" stroke="currentColor">
                <path d="M3 12h3m6-9v3m6 6h3m-6 6v3"></path>
                <circle cx="12" cy="12" r="3"></circle>
              </svg>
            </div>
            <div class="card-info">
              <h3>Distance</h3>
              <span class="card-label">ระยะทาง</span>
            </div>
          </div>
          <div class="card-value">
            <span class="value" :style="{color: getColor('distance', sensorData.distance)}">
              {{ sensorData.distance }}
            </span>
            <span class="unit">cm</span>
          </div>
          <div :class="['status-indicator', getStatusClass('distance', sensorData.distance)]">
            {{ getStatus('distance', sensorData.distance) }}
          </div>
          <div class="stats-grid">
            <div class="stat">
              <span class="stat-label">Min</span>
              <span class="stat-value">{{ stats.distance.min }}</span>
            </div>
            <div class="stat">
              <span class="stat-label">Max</span>
              <span class="stat-value">{{ stats.distance.max }}</span>
            </div>
            <div class="stat">
              <span class="stat-label">Avg</span>
              <span class="stat-value">{{ stats.distance.avg }}</span>
            </div>
          </div>
        </div>
      </div>

      <!-- Chart Section -->
      <div class="chart-section">
        <div class="section-header">
          <h2>Historical Data</h2>
          <span class="data-count">{{ dataCount }} records</span>
        </div>
        <div class="chart-wrapper">
          <canvas ref="sensorChart"></canvas>
        </div>
      </div>

      <!-- System Info -->
      <div class="info-section">
        <div class="section-header">
          <h2>System Information</h2>
        </div>
        <div class="info-grid">
          <div class="info-card">
            <div class="info-icon">📡</div>
            <div class="info-content">
              <span class="info-label">Server</span>
              <span class="info-value">{{ serverUrl }}</span>
            </div>
          </div>
          <div class="info-card">
            <div class="info-icon">📊</div>
            <div class="info-content">
              <span class="info-label">Total Records</span>
              <span class="info-value">{{ dataCount }}</span>
            </div>
          </div>
          <div class="info-card">
            <div class="info-icon">⏱️</div>
            <div class="info-content">
              <span class="info-label">Last Update</span>
              <span class="info-value">{{ lastUpdate }}</span>
            </div>
          </div>
          <div class="info-card">
            <div class="info-icon">🔌</div>
            <div class="info-content">
              <span class="info-label">Connection</span>
              <span class="info-value" :style="{color: connectionStatus === 'connected' ? '#10b981' : '#ef4444'}">
                {{ connectionStatus === 'connected' ? 'Active' : 'Inactive' }}
              </span>
            </div>
          </div>
        </div>
      </div>
    </main>
  </div>
</template>

<script>
import { Chart, registerables } from 'chart.js';
import { markRaw } from 'vue';
import { io } from 'socket.io-client';

Chart.register(...registerables);

export default {
  name: 'SensorDashboard',
  data() {
    return {
      socket: null,
      serverUrl: 'http://localhost:3000',
      connectionStatus: 'disconnected',
      sensorData: {
        temperature: '--',
        humidity: '--',
        mq2Value: '--',
        distance: '--'
      },
      chartData: {
        labels: [],
        temperature: [],
        humidity: [],
        mq2: [],
        distance: []
      },
      stats: {
        temperature: { min: '--', max: '--', avg: '--' },
        humidity: { min: '--', max: '--', avg: '--' },
        mq2: { min: '--', max: '--', avg: '--' },
        distance: { min: '--', max: '--', avg: '--' }
      },
      dataCount: 0,
      lastUpdate: '--:--:--',
      chart: null,
      maxDataPoints: 20
    }
  },
  mounted() {
    this.initChart();
    this.connectToSocket();
  },
  beforeUnmount() {
    if (this.socket) {
      this.socket.disconnect();
    }
    if (this.chart) {
      this.chart.destroy();
    }
  },
  methods: {
    connectToSocket() {
      this.socket = io(this.serverUrl, {
        reconnection: true,
        reconnectionDelay: 1000,
        reconnectionAttempts: 5
      });

      this.socket.on('connect', () => {
        console.log('Connected to Socket.IO server');
        this.connectionStatus = 'connected';
      });

      this.socket.on('sensorData', (data) => {
        console.log('Received sensor data:', data);
        this.updateSensorData(data);
      });

      this.socket.on('connect_error', (error) => {
        console.error('Connection error:', error);
        this.connectionStatus = 'disconnected';
      });

      this.socket.on('disconnect', () => {
        console.log('Disconnected from server');
        this.connectionStatus = 'disconnected';
      });
    },

    updateSensorData(data) {
      this.sensorData = {
        temperature: this.formatValue(data.temperature),
        humidity: this.formatValue(data.humidity),
        mq2Value: this.formatValue(data.mq2Value),
        distance: this.formatValue(data.distance)
      };
      
      this.addDataToHistory();
    },

    formatValue(value) {
      if (value === undefined || value === null || value === '--') {
        return '--';
      }
      return typeof value === 'number' ? parseFloat(value.toFixed(1)) : value;
    },

    initChart() {
      const ctx = this.$refs.sensorChart.getContext('2d');
      
      this.chart = markRaw(new Chart(ctx, {
        type: 'line',
        data: {
          labels: [],
          datasets: [
            {
              label: 'Temperature (°C)',
              data: [],
              borderColor: '#6366f1',
              backgroundColor: 'rgba(99, 102, 241, 0.1)',
              tension: 0.4,
              fill: true,
              borderWidth: 2
            },
            {
              label: 'Humidity (%)',
              data: [],
              borderColor: '#0ea5e9',
              backgroundColor: 'rgba(14, 165, 233, 0.1)',
              tension: 0.4,
              fill: true,
              borderWidth: 2
            },
            {
              label: 'Air Quality (PPM)',
              data: [],
              borderColor: '#f59e0b',
              backgroundColor: 'rgba(245, 158, 11, 0.1)',
              tension: 0.4,
              fill: true,
              borderWidth: 2
            },
            {
              label: 'Distance (cm)',
              data: [],
              borderColor: '#10b981',
              backgroundColor: 'rgba(16, 185, 129, 0.1)',
              tension: 0.4,
              fill: true,
              borderWidth: 2
            }
          ]
        },
        options: {
          responsive: true,
          maintainAspectRatio: true,
          aspectRatio: 2.5,
          plugins: {
            legend: {
              position: 'top',
              labels: {
                usePointStyle: true,
                padding: 15,
                font: {
                  size: 12,
                  family: "'Inter', sans-serif"
                }
              }
            }
          },
          scales: {
            y: {
              beginAtZero: true,
              grid: {
                color: '#f3f4f6'
              }
            },
            x: {
              grid: {
                display: false
              }
            }
          },
          animation: {
            duration: 750
          }
        }
      }));
    },

    addDataToHistory() {
      if (this.sensorData.temperature === '--') return;

      const now = new Date();
      const timeLabel = now.toLocaleTimeString('th-TH', { 
        hour: '2-digit', 
        minute: '2-digit', 
        second: '2-digit' 
      });

      this.chartData.labels.push(timeLabel);
      this.chartData.temperature.push(parseFloat(this.sensorData.temperature) || 0);
      this.chartData.humidity.push(parseFloat(this.sensorData.humidity) || 0);
      this.chartData.mq2.push((parseFloat(this.sensorData.mq2Value) || 0) );
      this.chartData.distance.push((parseFloat(this.sensorData.distance) || 0) );

      if (this.chartData.labels.length > this.maxDataPoints) {
        this.chartData.labels.shift();
        this.chartData.temperature.shift();
        this.chartData.humidity.shift();
        this.chartData.mq2.shift();
        this.chartData.distance.shift();
      }

      if (this.chart) {
        this.chart.data.labels = [...this.chartData.labels];
        this.chart.data.datasets[0].data = [...this.chartData.temperature];
        this.chart.data.datasets[1].data = [...this.chartData.humidity];
        this.chart.data.datasets[2].data = [...this.chartData.mq2];
        this.chart.data.datasets[3].data = [...this.chartData.distance];
        this.chart.update('none');
      }

      this.updateStats();
      this.dataCount++;
      this.lastUpdate = timeLabel;
    },
    
    updateStats() {
      const calcStats = (arr) => {
        if (arr.length === 0) return { min: '--', max: '--', avg: '--' };
        const min = Math.min(...arr);
        const max = Math.max(...arr);
        const avg = (arr.reduce((a, b) => a + b, 0) / arr.length).toFixed(1);
        return { 
          min: parseFloat(min.toFixed(1)), 
          max: parseFloat(max.toFixed(1)), 
          avg: parseFloat(avg) 
        };
      };

      if (this.chartData.temperature.length > 0) {
        this.stats.temperature = calcStats(this.chartData.temperature);
        this.stats.humidity = calcStats(this.chartData.humidity);
        this.stats.mq2 = {
          min: Math.floor(Math.min(...this.chartData.mq2) * 10),
          max: Math.floor(Math.max(...this.chartData.mq2) * 10),
          avg: Math.floor((this.chartData.mq2.reduce((a, b) => a + b, 0) / this.chartData.mq2.length) * 10)
        };
        this.stats.distance = {
          min: Math.floor(Math.min(...this.chartData.distance) * 10),
          max: Math.floor(Math.max(...this.chartData.distance) * 10),
          avg: Math.floor((this.chartData.distance.reduce((a, b) => a + b, 0) / this.chartData.distance.length) * 10)
        };
      }
    },
    
    getColor(type, value) {
      if (value === '--') return '#9ca3af';
      
      if (type === 'temperature') {
        if (value > 30) return '#ef4444';
        if (value > 25) return '#f59e0b';
        return '#10b981';
      }
      if (type === 'humidity') {
        if (value > 70) return '#0ea5e9';
        if (value < 30) return '#f59e0b';
        return '#10b981';
      }
      if (type === 'mq2') {
        if (value > 600) return '#ef4444';
        if (value > 300) return '#f59e0b';
        return '#10b981';
      }
      if (type === 'distance') {
        if (value < 30) return '#ef4444';
        if (value < 100) return '#f59e0b';
        return '#10b981';
      }
    },
    
    getStatus(type, value) {
      if (value === '--') return 'Waiting...';
      
      if (type === 'temperature') {
        if (value > 30) return 'Very Hot';
        if (value > 25) return 'Warm';
        return 'Normal';
      }
      if (type === 'humidity') {
        if (value > 70) return 'Very Humid';
        if (value < 30) return 'Too Dry';
        return 'Normal';
      }
      if (type === 'mq2') {
        if (value > 600) return 'Dangerous';
        if (value > 300) return 'Caution';
        return 'Good';
      }
      if (type === 'distance') {
        if (value < 30) return 'Too Close';
        if (value < 100) return 'Close';
        return 'Safe';
      }
    },
    
    getStatusClass(type, value) {
      if (value === '--') return 'status-waiting';
      
      const color = this.getColor(type, value);
      if (color === '#ef4444') return 'status-danger';
      if (color === '#f59e0b') return 'status-warning';
      return 'status-normal';
    }
  }
}
</script>

<style scoped>
* {
  margin: 0;
  padding: 0;
  box-sizing: border-box;
}

.app-container {
  min-height: 100vh;
  background: #f8fafc;
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, 'Segoe UI', sans-serif;
}

/* Header Styles */
.app-header {
  background: #ffffff;
  border-bottom: 1px solid #e2e8f0;
  position: sticky;
  top: 0;
  z-index: 100;
  box-shadow: 0 1px 3px rgba(0, 0, 0, 0.05);
}

.header-content {
  max-width: 1400px;
  margin: 0 auto;
  padding: 20px 24px;
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.header-left {
  display: flex;
  align-items: center;
}

.logo {
  display: flex;
  align-items: center;
  gap: 12px;
}

.logo-icon {
  width: 44px;
  height: 44px;
  background: linear-gradient(135deg, #6366f1 0%, #8b5cf6 100%);
  border-radius: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 22px;
}

.logo-text h1 {
  font-size: 1.25rem;
  font-weight: 700;
  color: #0f172a;
  line-height: 1.2;
}

.logo-text p {
  font-size: 0.75rem;
  color: #64748b;
  margin-top: 2px;
}

.header-right {
  display: flex;
  align-items: center;
  gap: 24px;
}

.connection-status,
.last-update {
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 0.875rem;
  color: #475569;
}

.status-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  animation: pulse 2s infinite;
}

.status-dot.connected {
  background: #10b981;
}

.status-dot.disconnected {
  background: #ef4444;
  animation: none;
}

@keyframes pulse {
  0%, 100% { opacity: 1; }
  50% { opacity: 0.5; }
}

.clock-icon {
  width: 16px;
  height: 16px;
  stroke-width: 2;
  color: #64748b;
}

/* Main Content */
.main-content {
  max-width: 1400px;
  margin: 0 auto;
  padding: 24px;
}

/* Sensor Grid */
.sensor-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(280px, 1fr));
  gap: 20px;
  margin-bottom: 24px;
}

.sensor-card {
  background: #ffffff;
  border: 1px solid #e2e8f0;
  border-radius: 12px;
  padding: 24px;
  transition: all 0.2s ease;
}

.sensor-card:hover {
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.08);
  transform: translateY(-2px);
}

.card-header {
  display: flex;
  align-items: center;
  gap: 12px;
  margin-bottom: 20px;
}

.card-icon {
  width: 40px;
  height: 40px;
  border-radius: 10px;
  display: flex;
  align-items: center;
  justify-content: center;
}

.card-icon svg {
  width: 20px;
  height: 20px;
  stroke-width: 2;
}

.temp-icon {
  background: #eef2ff;
  color: #6366f1;
}

.humid-icon {
  background: #e0f2fe;
  color: #0ea5e9;
}

.mq2-icon {
  background: #fef3c7;
  color: #f59e0b;
}

.dist-icon {
  background: #d1fae5;
  color: #10b981;
}

.card-info h3 {
  font-size: 0.875rem;
  font-weight: 600;
  color: #0f172a;
  line-height: 1.2;
}

.card-label {
  font-size: 0.75rem;
  color: #94a3b8;
}

.card-value {
  margin-bottom: 16px;
  display: flex;
  align-items: baseline;
  gap: 6px;
}

.value {
  font-size: 2.5rem;
  font-weight: 700;
  line-height: 1;
}

.unit {
  font-size: 1rem;
  color: #94a3b8;
  font-weight: 500;
}

.status-indicator {
  display: inline-flex;
  align-items: center;
  padding: 4px 12px;
  border-radius: 6px;
  font-size: 0.75rem;
  font-weight: 600;
  margin-bottom: 16px;
}

.status-normal {
  background: #d1fae5;
  color: #065f46;
}

.status-warning {
  background: #fef3c7;
  color: #92400e;
}

.status-danger {
  background: #fee2e2;
  color: #991b1b;
}

.status-waiting {
  background: #f1f5f9;
  color: #64748b;
}

.stats-grid {
  display: grid;
  grid-template-columns: repeat(3, 1fr);
  gap: 12px;
  padding-top: 16px;
  border-top: 1px solid #f1f5f9;
}

.stat {
  text-align: center;
}

.stat-label {
  display: block;
  font-size: 0.7rem;
  color: #94a3b8;
  margin-bottom: 4px;
  text-transform: uppercase;
  letter-spacing: 0.5px;
}

.stat-value {
  display: block;
  font-size: 0.875rem;
  font-weight: 600;
  color: #334155;
}

/* Chart Section */
.chart-section {
  background: #ffffff;
  border: 1px solid #e2e8f0;
  border-radius: 12px;
  padding: 24px;
  margin-bottom: 24px;
}

.section-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 20px;
}

.section-header h2 {
  font-size: 1.125rem;
  font-weight: 600;
  color: #0f172a;
}

.data-count {
  font-size: 0.875rem;
  color: #64748b;
}

.chart-wrapper {
  position: relative;
}

/* Info Section */
.info-section {
  background: #ffffff;
  border: 1px solid #e2e8f0;
  border-radius: 12px;
  padding: 24px;
}

.info-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(240px, 1fr));
  gap: 16px;
}

.info-card {
  display: flex;
  align-items: center;
  gap: 12px;
  padding: 16px;
  background: #f8fafc;
  border-radius: 8px;
  border: 1px solid #f1f5f9;
}

.info-icon {
  font-size: 24px;
}

.info-content {
  display: flex;
  flex-direction: column;
  gap: 4px;
}

.info-label {
  font-size: 0.75rem;
  color: #64748b;
  font-weight: 500;
}

.info-value {
  font-size: 0.875rem;
  color: #0f172a;
  font-weight: 600;
}

/* Responsive */
@media (max-width: 768px) {
  .header-content {
    flex-direction: column;
    gap: 16px;
    align-items: flex-start;
  }
  
  .header-right {
    width: 100%;
    justify-content: space-between;
  }
  
  .sensor-grid {
    grid-template-columns: 1fr;
  }
  
  .value {
    font-size: 2rem;
  }
}
</style>