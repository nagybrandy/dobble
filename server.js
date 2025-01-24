const express = require("express");
const multer = require("multer");
const fs = require("fs");
const { exec } = require("child_process");

const app = express();
const port = 3000;

// Multer setup for image uploads
const upload = multer({ dest: "uploads/" });

// Serve frontend files
app.use(express.static("public"));

// Handle form submission
app.post("/generate", upload.array("images"), (req, res) => {
    const { gameType, symbolCount, symbolType, appearanceType } = req.body;

    // Write user inputs to a configuration file
    const configData = `${gameType}\n${symbolCount}\n${symbolType}\n${appearanceType}\n`;
    fs.writeFileSync("config.txt", configData);

    console.log("Configuration saved. Running C++ program...");

    // Run compiled C++ program
    exec("./dobble_generator < config.txt", (error, stdout, stderr) => {
        if (error) {
            console.error(`Error: ${error.message}`);
            return res.json({ success: false, error: "Error generating PDF." });
        }
        if (stderr) {
            console.error(`stderr: ${stderr}`);
        }
        console.log(`stdout: ${stdout}`);

        // Check if the PDF exists
        const pdfPath = "public/dobble_cards.pdf";
        if (fs.existsSync(pdfPath)) {
            return res.json({ success: true, pdfUrl: "/dobble_cards.pdf" });
        } else {
            return res.json({ success: false, error: "PDF not found." });
        }
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}`);
});
