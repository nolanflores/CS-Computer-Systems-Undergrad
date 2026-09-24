const fs = require("fs")
const path = require("path")
const userEvent = require("@testing-library/user-event").default
const { screen } = require("@testing-library/dom")

const htmlPath = path.join(__dirname, "registerUser/registerUser.html")
const scriptPath = path.join(__dirname, "registerUser/registerUser.js")

function loadApp() {
  const html = fs.readFileSync(htmlPath, "utf8")
  const body = html.match(/<body[^>]*>([\s\S]*)<\/body>/i)[1]

  document.body.innerHTML = body
  jest.resetModules()
  require(scriptPath)
}

beforeEach(() => {
  loadApp()
})

test("successful registration shows success and clears the form", async () => {
  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/email/i), "test@example.com")
  await user.type(screen.getByLabelText(/password/i), "Abcdef1!")
  await user.click(screen.getByRole("button", { name: /register/i }))

  expect(screen.getByRole("status")).toHaveTextContent(
    "You have successfully registered."
  )
  expect(screen.getByLabelText(/email/i)).toHaveValue("")
  expect(screen.getByLabelText(/password/i)).toHaveValue("")
})

test("missing email shows the email error", async () => {
  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/password/i), "Abcdef1!")
  await user.click(screen.getByRole("button", { name: /register/i }))

  expect(screen.getByRole("alert")).toHaveTextContent(
    "The email address you entered is invalid."
  )
})

test("missing password shows the password error", async () => {
  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/email/i), "test@example.com")
  await user.click(screen.getByRole("button", { name: /register/i }))

  expect(screen.getByRole("alert")).toHaveTextContent(
    "The password you entered is invalid."
  )
})

test("invalid password shows specific password requirements", async () => {
  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/email/i), "test@example.com")
  await user.type(screen.getByLabelText(/password/i), "abcdefgh")
  await user.click(screen.getByRole("button", { name: /register/i }))

  const alert = screen.getByRole("alert")
  expect(alert).toHaveTextContent("The password you entered is invalid.")
  expect(alert).toHaveTextContent("Password needs an upper case letter")
  expect(alert).toHaveTextContent("Password needs a numeric digit (0-9)")
  expect(alert).toHaveTextContent("Password needs a symbol (!@#$%^&*)")
})