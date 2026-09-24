require("@testing-library/jest-dom")

// Polyfill fetch and related globals for jsdom environment
if (!global.fetch) {
  const fetch = require("node-fetch")
  global.fetch = fetch
  global.Request = fetch.Request
  global.Response = fetch.Response
  global.Headers = fetch.Headers
}