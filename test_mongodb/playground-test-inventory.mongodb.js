/* global use, db */
// MongoDB Playground
// To disable this template go to Settings | MongoDB | Use Default Template For Playground.
// Make sure you are connected to enable completions and to be able to run a playground.
// Use Ctrl+Space inside a snippet or a string literal to trigger completions.
// The result of the last command run in a playground is shown on the results panel.
// By default the first 20 documents will be returned with a cursor.
// Use 'console.log()' to print to the debug output.
// For more documentation on playgrounds please refer to
// https://www.mongodb.com/docs/mongodb-vscode/playgrounds/

// Select the database to use.
use('test');

// Insert a few documents into the sales collection.
db.getCollection('inventory').insertMany([
    { "item": "journal", "qty": 25, "size": { "h": 14, "w": 21, "uom": "cm" }, "status": "A" },
    { "item": "notebook", "qty": 50, "size": { "h": 8.5, "w": 11, "uom": "in" }, "status": "A" },
    { "item": "paper", "qty": 100, "size": { "h": 8.5, "w": 11, "uom": "in" }, "status": "D" },
    { "item": "planner", "qty": 75, "size": { "h": 22.85, "w": 30, "uom": "cm" }, "status": "D" },
    { "item": "postcard", "qty": 45, "size": { "h": 10, "w": 15.25, "uom": "cm" }, "status": "A" }
]);

// select * from inventory; 
db.getCollection('inventory').find({}); 

//select * from inventory where status=="D";
db.getCollection("inventory").find({status:"A"}); 

// select * from inventory where item in ("journal", "notebook")
db.getCollection("inventory").find({item: {$in: ["journal", "notebook"]}}); 

// select * from inventory where status == 'A AND qty < 30;
db.getCollection("inventory").find({status:'A', qty:{$lt:30}})

// select * from inventory where status=='A or qty < 30
db.getCollection("inventory").find({$or:[{status:'A'}, {qty:{$lt:30}}]})

// select * from inventory where status =='A and (qty<30 or item like 'p%)
db.getCollection("inventory").find({ status:'A', $or:[{qty:{$lt:30}}, {item:{$regex:'^p'}}] })

// 以嵌套文档为查询条件时，需要全部字段进行精确匹配，且顺序不能改变。
db.getCollection("inventory").find({size:{h:14, w:21, uom:"cm"}})
db.getCollection("inventory").find({size:{w:21, h:14, uom:"cm"}}) // 颠倒顺序查询失败
db.getCollection("inventory").find({size:{w:21, h:14}}) //字段没有写全，查询失败

// 以嵌套文档的字段为查询条件
db.getCollection("inventory").find({'size.uom': 'in'});
db.getCollection("inventory").find({'size.h': {$lt:10}});
db.getCollection("inventory").find({'size.h': {$lt:15}, 
                                    'size.uom': 'in',
                                    status:'D'}
                                    );


                                    
// Run a find command to view items sold on April 4th, 2014.
const salesOnApril4th = db.getCollection('sales').find({
  date: { $gte: new Date('2014-04-04'), $lt: new Date('2014-04-05') }
}).count();

// Print a message to the output window.
console.log(`${salesOnApril4th} sales occurred in 2014.`);

// Here we run an aggregation and open a cursor to the results.
// Use '.toArray()' to exhaust the cursor to return the whole result set.
// You can use '.hasNext()/.next()' to iterate through the cursor page by page.
db.getCollection('sales').aggregate([
  // Find all of the sales that occurred in 2014.
  { $match: { date: { $gte: new Date('2014-01-01'), $lt: new Date('2015-01-01') } } },
  // Group the total sales for each product.
  { $group: { _id: '$item', totalSaleAmount: { $sum: { $multiply: [ '$price', '$quantity' ] } } } }
]);
