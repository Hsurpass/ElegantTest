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

db.getCollection('inventory').insertMany([
                                      {
                                        item: 'journal',
                                        qty: 25,
                                        tags: ['blank', 'red'],
                                        dim_cm: [14, 21]
                                      },
                                      {
                                        item: 'notebook',
                                        qty: 50,
                                        tags: ['red', 'blank'],
                                        dim_cm: [14, 21]
                                      },
                                      {
                                        item: 'paper',
                                        qty: 100,
                                        tags: ['red', 'blank', 'plain'],
                                        dim_cm: [14, 21]
                                      },
                                      {
                                        item: 'planner',
                                        qty: 75,
                                        tags: ['blank', 'red'],
                                        dim_cm: [22.85, 30]
                                      },
                                      {
                                        item: 'postcard',
                                        qty: 45,
                                        tags: ['blue'],
                                        dim_cm: [10, 15.25]
                                      }
]);


db.getCollection('orders').insertMany( [
  { _id: 0, name: "Pepperoni", size: "small", price: 19, quantity: 10, date: ISODate( "2021-03-13T08:14:30Z" ) },
  { _id: 1, name: "Pepperoni", size: "medium", price: 20,quantity: 20, date : ISODate( "2021-03-13T09:13:24Z" ) },
  { _id: 2, name: "Pepperoni", size: "large", price: 21, quantity: 30, date : ISODate( "2021-03-17T09:22:12Z" ) },
  { _id: 3, name: "Cheese", size: "small", price: 12, quantity: 15, date : ISODate( "2021-03-13T11:21:39.736Z" ) },
  { _id: 4, name: "Cheese", size: "medium", price: 13,quantity: 50, date : ISODate( "2022-01-12T21:23:13.331Z" ) },
  { _id: 5, name: "Cheese", size: "large", price: 14, quantity: 10, date : ISODate( "2022-01-12T05:08:13Z" ) },
  { _id: 6, name: "Vegan", size: "small", price: 17,  quantity: 10, date : ISODate( "2021-01-13T05:08:13Z" ) },
  { _id: 7, name: "Vegan", size: "medium", price: 18, quantity: 10, date : ISODate( "2021-01-13T05:10:13Z" ) }
] );

// 计算size 为 ‘medium’全部订单的数量
// select name as order_name, count(*) as totalQuantity where size == 'medium' group by name;
db.getCollection('orders').aggregate([
  {
    $match: { size: 'medium'}
  },

  {
    $group: { _id: "$name", totalQuantity: { $sum:'$quantity'  }}
  }
]);

// 计算某个时间段内，每天的订单总价值、订单数目、订单的平均数量，并基于订单总价值按降序排序。
// select sum(quantity * price) as order_total_value, count(*) as order_total_quantity, avg(order_total_num) as avg_quantity from orders where date > "2020-01-30" and date < "2022-01-30" group by date order by order_total_value;
db.getCollection('orders').aggregate([
  {
    $match: {
      date:{$gte: new ISODate('2020-01-30'), $lte:new ISODate('2022-01-30')}
    }
  },
  {
    $group:{
        _id:{$dateToString:{format:"%Y-%m-%d", date:'$date'}},
        totalOrderValue:{$sum:{$multiply:['$price', "$quantity"] }},
        totalOrderQuantity:{$sum:'$quantity'},
        documentCount: {$sum:1},
        averageOrderQuantity:{$avg:'$quantity'}
      }
  },
  {
    $sort: {
      totalOrderValue: -1
    }
  }

]);



// mongoimport --db=test --collection=zipcodes --file=zips.json --username="tester"
// 查找总人口大于1000万的地区
// 基于state字段进行分组，对每个分组中的pop字段进行求和，基于求和结果找到大于1000的文档
// select state, SUM(pop) as total_pop from zipcodes group by state having total_pop >= 10000000  

db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: '$state',
      total_pop: {
        $sum: '$pop'
      }
    }
  },
  {
    $match: {
      total_pop:{$gte:10000000}
    }
  }
]);

// 

db.getCollection('zipcodes').find({city:"PAWNEE"});
db.getCollection('zipcodes').find({state:"MA"});

db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state', city:'$city'},
      group_count:{$sum:1},
      total_city_pop: {
        $sum: '$pop'
      }
    }
  }
])


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
