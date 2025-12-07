const { PDFDocument } = require("pdf-lib");
const fs = require("fs");
const path = require("path");
const { fromBuffer } = require("pdf2pic");
const imageSplit = require("./imageSplitter.js");

// ----------------------------------------
// CONFIG
// ----------------------------------------
const PDF_PATH = "file.pdf";
const DPI = 300;
const OUTPUT_IMAGE_DIR = "./images";
const OUTPUT_CHUNK_DIR =
  "/home/ubuntu/Desktop/pdf-to-image-example/viewer-app/public/image_chunks";


// ----------------------------------------
// UTILITIES
// ----------------------------------------
function ensureDirectoryExists(dir) {
  if (!fs.existsSync(dir)) {
    fs.mkdirSync(dir, { recursive: true });
  }
}

ensureDirectoryExists(OUTPUT_IMAGE_DIR);
ensureDirectoryExists(OUTPUT_CHUNK_DIR);


// ----------------------------------------
// CONVERT PDF → IMAGES
// ----------------------------------------
async function convertPDFToImages(pdfPath) {
  const pdfBuffer = fs.readFileSync(pdfPath);
  const pdfDoc = await PDFDocument.load(pdfBuffer);
  const numPages = pdfDoc.getPageCount();

  const convert = fromBuffer(pdfBuffer, {
    density: DPI,
    savePath: OUTPUT_IMAGE_DIR,
    format: "png",
  });

  const filenames = [];

  for (let i = 1; i <= numPages; i++) {
    const name = `page_${i}`;
    try {
      const result = await convert(i, {
        responseType: "image",
        saveFilename: name,
      });
      console.log(`Converted page ${i} → ${result.name}`);
      filenames.push(result.name);
    } catch (err) {
      console.error(`Error converting page ${i}:`, err);
    }
  }

  return filenames;
}


// ----------------------------------------
// IMAGE → CHUNKS
// ----------------------------------------
async function splitImagesToChunks(filenames, chunkSize) {
  let rowIndex = 0;

  for (const filename of filenames) {
    const fullPath = path.join(OUTPUT_IMAGE_DIR, filename);

    try {
      const chunks = await imageSplit.imageToChunks(
        fullPath,
        chunkSize,
        chunkSize
      );

      console.log(`Split ${filename} into ${chunks.length} chunks`);

      // Assumes a perfect square grid — verify your splitter!
      const numCols = Math.sqrt(chunks.length);
      if (!Number.isInteger(numCols)) {
        console.warn(
          `⚠ ${filename}: chunk count (${chunks.length}) is not a perfect square; grid may misalign.`
        );
      }

      let colIndex = 0;

      chunks.forEach((chunk, idx) => {
        const chunkFilename = path.join(
          OUTPUT_CHUNK_DIR,
          `chunk_${rowIndex}_${colIndex}.png`
        );

        fs.writeFileSync(chunkFilename, chunk);
        // console.log(`Saved ${chunkFilename}`);

        colIndex++;
        if (colIndex >= numCols) {
          colIndex = 0;
          rowIndex++;
        }
      });
    } catch (err) {
      console.error(`Error splitting ${filename}:`, err);
    }
  }
}


// ----------------------------------------
// MAIN FLOW
// ----------------------------------------
(async () => {
  try {
    console.log("Starting PDF → Image → Chunks pipeline...");
    const filenames = await convertPDFToImages(PDF_PATH);
    await splitImagesToChunks(filenames, 100);
    console.log("Done!");
  } catch (err) {
    console.error("Fatal pipeline error:", err);
  }
})();
