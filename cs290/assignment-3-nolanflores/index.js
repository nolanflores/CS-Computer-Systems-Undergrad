/*
 * Write your client-side JS code in this file.  Don't forget to include your
 * name and @oregonstate.edu email address below.
 *
 * Name: Nolan Flores
 * Email: florenol@oregonstate.edu
 */

function openModal(){
    document.getElementById("modal-backdrop").classList.remove("hidden");
    document.getElementById("sell-something-modal").classList.remove("hidden");
}

function closeModal(){
    document.getElementById("modal-backdrop").classList.add("hidden");
    document.getElementById("sell-something-modal").classList.add("hidden");
    document.getElementById("post-text-input").value = "";
    document.getElementById("post-photo-input").value = "";
    document.getElementById("post-price-input").value = "";
    document.getElementById("post-city-input").value = "";
}

function createPost(){
    const postText = document.getElementById("post-text-input").value;
    const postPhoto = document.getElementById("post-photo-input").value;
    const postPrice = document.getElementById("post-price-input").value;
    const postCity = document.getElementById("post-city-input").value;
    const conditions = document.getElementsByName("post-condition");
    let postCondition = null;
    for(const c of conditions){
        if(c.checked){
            postCondition = c.value;
        }
    }
    if(!(postCity && postPhoto && postPrice && postText && postCondition)){
        alert("Please fill out all fields.");
        return;
    }
    const container = document.createElement("div");
    container.classList.add("post");
    container.dataset.price = postPrice;
    container.dataset.city = postCity;
    container.dataset.condition = postCondition;//CHANGE THIS TO CONDITION

    const contents = document.createElement("div");
    contents.classList.add("post-contents");
    container.appendChild(contents);

    const imageContainer = document.createElement("div");
    imageContainer.classList.add("post-image-container");
    contents.appendChild(imageContainer);

    const image = document.createElement("img");
    image.src = postPhoto;
    image.alt = postText;
    imageContainer.appendChild(image);

    const info = document.createElement("div");
    info.classList.add("post-info-container");
    contents.appendChild(info);

    const title = document.createElement("a");
    title.href = "#";
    title.classList.add("post-title");
    title.textContent = postText;
    info.appendChild(title);

    const price = document.createElement("span");
    price.classList.add("post-price");
    price.textContent = "$" + postPrice;
    info.appendChild(price);

    const city = document.createElement("span");
    city.classList.add("post-city");
    city.textContent = postCity;
    info.appendChild(city);

    document.getElementById("posts").appendChild(container);
    closeModal();

    const cityOptions = document.getElementById("filter-city").getElementsByTagName("option");
    const cities = [];
    for(const city of cityOptions){
        cities.push(city.value);
    }
    if(!cities.includes(postCity)){
        const option = document.createElement("option");
        option.value = postCity;
        option.textContent = postCity;
        document.getElementById("filter-city").appendChild(option);
    }
}

function filter(){
    const posts = document.getElementsByClassName("post");
    for(const post of posts){
        post.classList.remove("hidden");
    }
    const text = document.getElementById("filter-text").value;
    const minPrice = document.getElementById("filter-min-price").value;
    const maxPrice = document.getElementById("filter-max-price").value;
    const city = document.getElementById("filter-city").value;
    const conditions = document.getElementsByName("filter-condition");
    const condition = [];
    for(const c of conditions){
        if(c.checked){
            condition.push(c.value);
        }
    }
    console.log(condition);
    for(const post of posts){
        const postText = post.getElementsByClassName("post-title")[0].textContent;
        const postPrice = post.dataset.price;
        const postCity = post.dataset.city;
        const postCondition = post.dataset.condition;
        if(text && !postText.toLowerCase().includes(text.toLowerCase())){
            post.classList.add("hidden");
        }
        if(minPrice && parseInt(postPrice) < parseInt(minPrice)){
            post.classList.add("hidden");
        }
        if(maxPrice && parseInt(postPrice) > parseInt(maxPrice)){
            post.classList.add("hidden");
        }
        if(city && !postCity.toLowerCase().includes(city.toLowerCase())){
            post.classList.add("hidden");
        }
        if(condition.length > 0 && !condition.includes(postCondition)){
            post.classList.add("hidden");
        }
    }
}

document.getElementById("sell-something-button").addEventListener("click", openModal);
document.getElementById("modal-cancel").addEventListener("click", closeModal);
document.getElementById("modal-close").addEventListener("click", closeModal);
document.getElementById("modal-accept").addEventListener("click", createPost);
document.getElementById("filter-update-button").addEventListener("click", filter);