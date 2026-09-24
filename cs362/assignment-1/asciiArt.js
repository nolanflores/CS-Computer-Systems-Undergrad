import figlet from "figlet"

const asciiText = process.argv[2];
console.log(asciiText);

async function drawAsciiArt(){
	const art = await figlet.text(asciiText);
	console.log(art);
}

drawAsciiArt();
