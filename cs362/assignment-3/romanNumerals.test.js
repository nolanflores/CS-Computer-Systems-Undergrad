const fs = require("fs")
const path = require("path")
const userEvent = require("@testing-library/user-event").default
const { screen } = require("@testing-library/dom")
const { rest } = require("msw")
const { setupServer } = require("msw/node")

const htmlPath = path.join(__dirname, "romanNumerals/romanNumerals.html")
const scriptPath = path.join(__dirname, "romanNumerals/romanNumerals.js")

const server = setupServer()

function loadApp() {
  const html = fs.readFileSync(htmlPath, "utf8")
  const body = html.match(/<body[^>]*>([\s\S]*)<\/body>/i)[1]

  document.body.innerHTML = body
  jest.resetModules()
  require(scriptPath)
}

beforeAll(() => server.listen())
afterEach(() => server.resetHandlers())
afterAll(() => server.close())

beforeEach(() => {
  loadApp()
})

test("old Roman numeral updates live as the user types", async () => {
  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/arabic number/i), "9")

  expect(screen.getByText("VIIII")).toBeInTheDocument()
})

test("submitting the form shows the modern Roman numeral from the API", async () => {
  server.use(
    rest.get("https://romans.justyy.workers.dev/api/romans/", (req, res, ctx) => {
      if (req.url.searchParams.get("n") === "9") {
        return res(ctx.json({ result: "IX" }))
      }
      return res(ctx.status(400), ctx.json({ error: "unexpected input" }))
    })
  )

  const user = userEvent.setup()

  await user.type(screen.getByLabelText(/arabic number/i), "9")
  await user.click(
    screen.getByRole("button", { name: /convert to "modern" roman/i })
  )

  expect(await screen.findByText("IX")).toBeInTheDocument()
})

test("changing the arabic number clears the modern Roman numeral", async () => {
  server.use(
    rest.get("https://romans.justyy.workers.dev/api/romans/", (req, res, ctx) => {
      if (req.url.searchParams.get("n") === "9") {
        return res(ctx.json({ result: "IX" }))
      }
      return res(ctx.json({ result: "X" }))
    })
  )

  const user = userEvent.setup()
  const input = screen.getByLabelText(/arabic number/i)
  const modernResult = document.getElementById("modern-roman-result")

  await user.type(input, "9")
  await user.click(
    screen.getByRole("button", { name: /convert to "modern" roman/i })
  )

  expect(await screen.findByText("IX")).toBeInTheDocument()

  await user.clear(input)
  await user.type(input, "10")

  expect(modernResult).toHaveTextContent("")
})