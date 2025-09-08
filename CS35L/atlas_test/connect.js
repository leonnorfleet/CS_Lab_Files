const { MongoClient } = require("mongodb");
const { boolean } = require("webidl-conversions");
 
// Replace the following with your Atlas connection string                                                                                                                                        
const url = "mongodb+srv://Cluster75631:XWtqYG1wb1NF@cluster75631.wxf12d8.mongodb.net/?retryWrites=true&w=majority";

// Connect to your Atlas cluster
const client = new MongoClient(url);

const dbName = "gettingStarted";

async function run() {
    try {
        // Connect to the Atlas cluster
        await client.connect();
        const db = client.db(dbName);

        // Reference the "people" collection in the specified database
        const col = db.collection("people");

        // Create a new document                                                                                                                                           
        let personDocument = {
            "name": { "first": "Alan", "last": "Turing" },
            "birth": new Date(1912, 5, 23), // May 23, 1912                                                                                                                                 
            "death": new Date(1954, 5, 7),  // May 7, 1954                                                                                                                                  
            "contribs": [ "Turing machine", "Turing test", "Turingery" ],
            "views": 1250000
        }

        // Find and return the document
        var first = "Blan";
        var last = "Turing";
        const filter = { "name.last": last, "name.first": first };
        const document = await col.findOne(filter);

        if (boolean(document)) {
            console.log("Document found:\n" + JSON.stringify(document));
        }
        else {
            console.log("Document not found:\nUploading as new person");
            personDocument.name.first = first;
            personDocument.name.last = last;

        // Insert the document into the specified collection        
            const p = await col.insertOne(personDocument);
        }

    } catch (err) {
        console.log(err.stack);
    }
    finally {
        await client.close();
    }
}

run().catch(console.dir);