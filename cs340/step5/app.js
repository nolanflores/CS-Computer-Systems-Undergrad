/*
    SETUP
*/

// Express
const express = require('express');
const bodyParser = require('body-parser');
const cors = require('cors');
const app = express();

app.use(cors());
app.use(bodyParser.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static('public'));

const PORT = 24087;

// Database 
const db = require('./database/db-connector');

// Filepath

const { engine } = require('./node_modules/express-handlebars'); // Import express-handlebars engine
app.engine('.hbs', engine({ extname: '.hbs' })); // Create instance of handlebars
app.set('view engine', '.hbs'); // Use handlebars engine for *.hbs files.
/*
    ROUTES
*/

app.get('/', async function(req, res) {
  try {
    res.render('home'); // Renders home.hbs file
  } catch (error) {
    console.error('Error rendering page:', error);
    // Sends a generic error to the browser
    res.status(500).send('An error occurred while rendering the page')
  }
});

app.post('/api/reset-db', async(req, res) => {
  try {
    const result = await db.query('CALL sp_reset_sstevedb()');
    res.json({success:true, data: result.rows});
  } catch (error) {
    console.error(error);
    res.status(500).json({success: false, error: 'Database error' });
  }
});

app.get('/sales', async function(req, res) {
  try {
    const query1 = 'SELECT * FROM Sales';
    const [rows] = await db.query(query1);

    if (rows.length === 0) {
      return res.render('sales', { headers: [], salesData: [] });
    }

    const headers = Object.keys(rows[0]);

    const salesData = rows.map(row => {
      return headers.map(header => row[header]);
    })

    res.render('sales', {
      headers: headers, 
      salesData: salesData
    });

    console.log("Sales data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Sales databases queries'
    );
  }
});

app.post('/insert-sale', async (req, res) => {
  const { 
      entity, 
      operation, 
      customerID, 
      employeeID, 
      productID, 
      locationID, 
      saleDate, 
      amount 
  } = req.body;

  try {
      const callQuery = `
          CALL insert_sale_record(?, ?, ?, ?, ?, ?, ?, ?, @new_id)
      `;
      const values = [entity, operation, customerID, employeeID, productID, locationID, saleDate, amount];
      
      await db.execute(callQuery, values);

      const [rows] = await db.execute('SELECT @new_id AS insertId');
      const newInsertId = rows[0].insertId;

      console.log(`Inserted row id: ${newInsertId}`);
      
      res.redirect(req.get('referer'));

  } catch (err) {
      if (err.sqlState === '45000') {
          return res.status(400).send(err.message); 
      }

      console.error('Database insertion error:', err);
      res.status(500).send('Database Error');
  }
});

app.get('/customers', async function(req, res) {
  try {
    const query1 = 'SELECT * FROM Customers';
    const [rows] = await db.query(query1);

    if (rows.length === 0) {
      return res.render('customers', { headers: [], custData: [] });
    }

    const headers = Object.keys(rows[0]);

    const custData = rows.map(row => {
      return headers.map(header => row[header]);
    })

    res.render('customers', {
      headers: headers, 
      custData: custData
    });

    console.log("Customer data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Customers databases queries'
    );
  }
});

app.get('/employees', async function(req, res) {
    try {
      const query1 = 'SELECT * FROM Employees';
      const [rows] = await db.query(query1);

      if (rows.length === 0) {
        return res.render('employees', { headers: [], empData: [] });
      }

      const headers = Object.keys(rows[0]);

      const empData = rows.map(row => {
        return headers.map(header => row[header]);
      })

      res.render('employees', {
        headers: headers, 
        empData: empData
      });

      console.log("Employee data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Employees database queries'
    );
  }
});

app.get('/guitars', async function(req, res) {
  try {
      const query1 = 'SELECT * FROM Guitars';
      const [rows] = await db.query(query1);

      if (rows.length === 0) {
        return res.render('guitars', { headers: [], guitarData: [] });
      }

      const headers = Object.keys(rows[0]);

      const guitarData = rows.map(row => {
        return headers.map(header => row[header]);
      })

      res.render('guitars', {
        headers: headers, 
        guitarData: guitarData
      });

      console.log("Guitar data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Guitar database queries'
    );
  }
});

app.get('/locations', async function(req, res) {
  try {
      const query1 = 'SELECT * FROM Locations';
      const [rows] = await db.query(query1);

      if (rows.length === 0) {
        return res.render('locations', { headers: [], locData: [] });
      }

      const headers = Object.keys(rows[0]);

      const locData = rows.map(row => {
        return headers.map(header => row[header]);
      })

      res.render('locations', {
        headers: headers, 
        locData: locData
      });

      console.log("Location data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Location database queries'
    );
  }
});

app.get('/roles', async function(req, res) {
  try {
      const query1 = 'SELECT * FROM Roles';
      const [rows] = await db.query(query1);

      if (rows.length === 0) {
        return res.render('roles', { headers: [], roleData: [] });
      }

      const headers = Object.keys(rows[0]);

      const roleData = rows.map(row => {
        return headers.map(header => row[header]);
      })

      res.render('roles', {
        headers: headers, 
        roleData: roleData
      });

      console.log("Role data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Role database queries'
    );
  }
});

app.get('/lessons', async function(req, res) {
    try {
      const query1 = 'SELECT * FROM Lessons';
      const [rows] = await db.query(query1);

      if (rows.length === 0) {
        return res.render('lessons', { headers: [], lessonData: [] });
      }

      const headers = Object.keys(rows[0]);

      const lessonData = rows.map(row => {
        return headers.map(header => row[header]);
      })

      res.render('lessons', {
        headers: headers, 
        lessonData: lessonData
      });

      console.log("Lesson data loaded successfully!");
  } catch (error) {
    console.error('Error executing queries: ', error);
    // Send a generic error message to the browser
    res.status(500).send(
      'An error occurred while executing the Lesson database queries'
    );
  }
});

app.post('/update-lesson', async (req, res) => {
  const { 
      customerID, 
      employeeID, 
      locationID, 
      lessonRate, 
      lessonInst
  } = req.body;

  try {
      const callQuery = `
          CALL sp_update_lesson(?, ?, ?, ?, ?)
      `;
      
      const values = [customerID, employeeID, locationID, lessonRate, lessonInst];
      
      await db.execute(callQuery, values);

      console.log(`Updated lesson for Customer ID: ${customerID} and Employee ID: ${employeeID}`);
      
      res.redirect(req.get('referer'));

  } catch (err) {
      if (err.sqlState === '45000') {
          return res.status(400).send(err.message); 
      }

      console.error('Database update error:', err);
      res.status(500).send('Database Error');
  }
});

app.post('/delete-lesson', async (req, res) => {
    const { 
        customerID, 
        employeeID 
    } = req.body;

    try {
        const callQuery = `
            CALL sp_delete_lesson(?, ?)
        `;
        
        const values = [customerID, employeeID];
        
        await db.execute(callQuery, values);

        console.log(`Deleted lesson for Customer ID: ${customerID} and Employee ID: ${employeeID}`);
        
        res.redirect(req.get('referer'));

    } catch (err) {
        if (err.sqlState === '45000') {
            return res.status(400).send(err.message); 
        }

        console.error('Database deletion error:', err);
        res.status(500).send('Database Error');
    }
});

/*
    LISTENER
*/

app.listen(PORT, function(){            // This is the basic syntax for what is called the 'listener' which receives incoming requests on the specified PORT.
    console.log('Express started on http://localhost:' + PORT + '; press Ctrl-C to terminate.')
});
