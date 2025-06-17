import React from 'react';
import ReactDOM from 'react-dom/client';
import './index.css';
import App from './App';
import reportWebVitals from './reportWebVitals';
import { WalletProvider } from '@suiet/wallet-kit';  // Asigură-te că ai importat corect WalletProvider

const root = ReactDOM.createRoot(document.getElementById('root'));
root.render(
  <WalletProvider>
    <App />
  </WalletProvider>
);

// Măsurarea performanței
reportWebVitals();
