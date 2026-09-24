// Initial References
const letterContainer = document.getElementById("letter-container");
const optionsContainer = document.getElementById("options-container");
const userInputSection = document.getElementById("user-input-section");
const newGameContainer = document.getElementById("new-game-container");
const newGameButton = document.getElementById("new-game-button");
const canvas = document.getElementById("canvas");
const resultText = document.getElementById("result-text");

// Options values for buttons
let options = {
  fruits: ["Apple", "Blueberry", "Mandarin", "Pineapple", "Pomegranate", "Watermelon"],
  animals: ["Hedgehog", "Rhinoceros", "Squirrel", "Panther", "Walrus", "Zebra"],
  countries: ["India", "Hungary", "Kyrgyzstan", "Switzerland", "Zimbabwe", "Dominica"],
};
//get words stored on the server
(async () => {
  let w = await fetch('/hangmanwords', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
    }
  });
  w = await w.json();
  for(let key in w){
    for(let word of w[key]){
      if(options[key]){
        options[key].push(word);
      }
    }
  }
})();

// Count
let winCount = 0;
let count = 0;

let chosenWord = "";

// Display option buttons
const displayOptions = () => {
  optionsContainer.innerHTML += `<h3>Please Select An Option</h3>`;
  let buttonCon = document.createElement("div");
  for (let value in options) {
    buttonCon.innerHTML += `<button class="options" onclick="generateWord('${value}')">${value}</button>`;
  }
  optionsContainer.appendChild(buttonCon);
};

// Block all buttons
const blocker = () => {
  let optionsButtons = document.querySelectorAll(".options");
  let letterButtons = document.querySelectorAll(".letters");
  // Disable all options
  optionsButtons.forEach((button) => (button.disabled = true));
  // Disable all letters
  letterButtons.forEach((button) => (button.disabled = true));
  newGameContainer.classList.remove("hide");
};

// Word Generator
const generateWord = (optionValue) => {
  let optionsButtons = document.querySelectorAll(".options");
  // Highlight the selected button
  optionsButtons.forEach((button) => {
    if (button.innerText.toLowerCase() === optionValue) {
      button.classList.add("active");
    }
    button.disabled = true;
  });

  // Show letters and clear previous word
  letterContainer.classList.remove("hide");
  userInputSection.innerText = "";

  let optionArray = options[optionValue];
  // Choose a random word
  chosenWord = optionArray[Math.floor(Math.random() * optionArray.length)].toUpperCase();

  // Replace every letter with underscores
  let displayItem = chosenWord.replace(/./g, '<span class="dashes">_</span>');
  userInputSection.innerHTML = displayItem;
};

// Initial Function
const initializer = () => {
  winCount = 0;
  count = 0;

  // Reset UI
  userInputSection.innerHTML = "";
  optionsContainer.innerHTML = "";
  letterContainer.classList.add("hide");
  newGameContainer.classList.add("hide");
  letterContainer.innerHTML = "";

  // Reset Canvas
  let { initialDrawing } = canvasCreator();
  initialDrawing();

  // Create letter buttons
  for (let i = 65; i < 91; i++) {
    let button = document.createElement("button");
    button.classList.add("letters");
    button.innerText = String.fromCharCode(i); // ASCII [A-Z]
    // Button click handler
    button.addEventListener("click", () => {
      let charArray = chosenWord.split("");
      let dashes = document.getElementsByClassName("dashes");
      if (charArray.includes(button.innerText)) {
        charArray.forEach((char, index) => {
          if (char === button.innerText) {
            dashes[index].innerText = char;
            winCount++;
            if (winCount == charArray.length) {
              resultText.innerHTML = `<h2 class='win-msg'>You Win!!</h2><p>The word was <span>${chosenWord}</span></p>`;
              fetch('/hangman', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({win: true}),
              });
              blocker();
            }
          }
        });
      } else {
        count++;
        drawMan(count);
        if (count == 6) {
          resultText.innerHTML = `<h2 class='lose-msg'>You Lose!!</h2><p>The word was <span>${chosenWord}</span></p>`;
          fetch('/hangman', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({win: false}),
          });
          blocker();
        }
      }
      button.disabled = true; // Disable button after click
    });
    letterContainer.append(button);
  }

  displayOptions();
};

// Canvas Drawing with Animation
const canvasCreator = () => {
  let context = canvas.getContext("2d");
  context.strokeStyle = "#000";
  context.lineWidth = 2;

  // Animated line drawing
  const drawLineAnimated = (fromX, fromY, toX, toY, duration) => {
    const steps = 50; // Number of animation steps
    const interval = duration / steps; // Time per step
    let step = 0;

    const deltaX = (toX - fromX) / steps;
    const deltaY = (toY - fromY) / steps;

    const drawStep = () => {
      if (step <= steps) {
        context.beginPath();
        context.moveTo(fromX + step * deltaX, fromY + step * deltaY);
        context.lineTo(fromX + (step + 1) * deltaX, fromY + (step + 1) * deltaY);
        context.stroke();
        step++;
        setTimeout(drawStep, interval);
      }
    };
    drawStep();
  };

  // Head animation
  const head = () => {
    let radius = 10;
    let startAngle = 0;
    let endAngle = Math.PI * 2;
    let steps = 50;
    let interval = 20; // Milliseconds per step
    let step = 0;

    const drawStep = () => {
      if (step <= steps) {
        context.beginPath();
        context.arc(70, 30, radius, startAngle, (endAngle * step) / steps);
        context.stroke();
        step++;
        setTimeout(drawStep, interval);
      }
    };
    drawStep();
  };

  // Body parts
  const body = () => drawLineAnimated(70, 40, 70, 80, 500);
  const leftArm = () => drawLineAnimated(70, 50, 50, 70, 500);
  const rightArm = () => drawLineAnimated(70, 50, 90, 70, 500);
  const leftLeg = () => drawLineAnimated(70, 80, 50, 110, 500);
  const rightLeg = () => drawLineAnimated(70, 80, 90, 110, 500);

  // Initial frame
  const initialDrawing = () => {
    context.clearRect(0, 0, canvas.width, canvas.height);
    drawLineAnimated(10, 130, 130, 130, 500); // Base
    drawLineAnimated(10, 10, 10, 131, 500); // Left vertical
    drawLineAnimated(10, 10, 70, 10, 500); // Top horizontal
    drawLineAnimated(70, 10, 70, 20, 500); // Small top
  };

  return { initialDrawing, head, body, leftArm, rightArm, leftLeg, rightLeg };
};

// Draw the hangman
const drawMan = (count) => {
  let { head, body, leftArm, rightArm, leftLeg, rightLeg } = canvasCreator();
  switch (count) {
    case 1:
      head();
      break;
    case 2:
      body();
      break;
    case 3:
      leftArm();
      break;
    case 4:
      rightArm();
      break;
    case 5:
      leftLeg();
      break;
    case 6:
      rightLeg();
      break;
    default:
      break;
  }
};

// New Game
newGameButton.addEventListener("click", initializer);
window.onload = initializer;

// Dynamic Word Addition
const addWordButton = document.getElementById("add-word-button");
const categorySelect = document.getElementById("category");
const newWordInput = document.getElementById("new-word");

addWordButton.addEventListener("click", () => {
  const selectedCategory = categorySelect.value;
  const newWord = newWordInput.value.trim();

  // Validate input
  if (newWord === "" || !/^[a-zA-Z]+$/.test(newWord)) {
    alert("Please enter a valid word containing only letters.");
    return;
  }

  // Add the new word to the selected category
  options[selectedCategory].push(newWord.charAt(0).toUpperCase() + newWord.slice(1).toLowerCase());
  fetch('/hangmanwords', {
    method: 'POST',
    headers: {
        'Content-Type': 'application/json',
    },
    body: JSON.stringify({newWord: newWord, category:selectedCategory}),
  });

  
  // Clear the input
  newWordInput.value = "";

  alert(`"${newWord}" has been added to the ${selectedCategory} category!`);
});

// Load saved options from localStorage on page load
window.onload = () => {
  initializer(); // Call your initializer to reset the game
};