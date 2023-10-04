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


db.getCollection('zipcodes').find({city:"PAWNEE"});
db.getCollection('zipcodes').find({state:"MN"});

// 基于state和city两个字段组合分组，只有两个字段的值都一样才会被分成一组。
// select COUNT(*) FROM zipcodes group by state, city;
db.getCollection('zipcodes').aggregate( [
  { 
    $group: {
      _id: { state: "$state", city: "$city" }, pop: { $sum: "$pop" } ,
      group_count:{$sum:1},
      total_city_pop: {
        $sum: '$pop'
      }
    }
  },
  {
    $match : {'_id.state':"CO", '_id.city':"EDGEWATER"}
  }
] )

// 计算某个州有多少城市
db.getCollection('zipcodes').aggregate([
  {
    $match:{state:'MI'},
  },
  {
    $group:{
      _id:"$state", // city 有重复的记录，统计有误差
      city_count:{$sum:1}
    }
  }
])

db.getCollection('zipcodes').find({state:'MI'}).count();

db.getCollection('zipcodes').aggregate([
  {
    $match:{state:'MI'},
  },
  {
    $group:{
      _id:{state: "$state", city:"$city"},
      doc_count:{$sum:1}
    }
  },
  {
    $group: {
      _id: {state:'$_id.state'},
      city_count:{$sum:1}
    }
  }
])

db.getCollection('zipcodes').aggregate([
  {
    $match:{state:'MI'},
  },
  {
    $group:{
      _id:{state: "$state", city:"$city"},
      doc_count:{$sum:1}
    }
  },
  {
    $match: {
      doc_count:{$gt:2}
    }
  }
])

db.getCollection('zipcodes').find({state:'MI', city:"MUSKEGON"})

// 查看基于state字段可以分成几个组
// select count(*) as state_count from (select * from zipcodes group by state);
// select count(distinct state) as state_count from zipcodes;
// 方法1：
db.getCollection('zipcodes').aggregate([
  {
    $group:{
      _id:{state:'$state'}
    }
  },
  {
    $group:{
      _id:null,
      state_count:{$sum:1}
    }
  }
]); // 51

//方法2:
let result = db.getCollection('zipcodes').distinct('state');
console.log(result.length); // 51
// 方法3：
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id:null,
      values: {$addToSet:'$state'},
    }
  },
  {
    $project: {
      arr_size : { $size: '$values'} 
    }
  }
]); //51

// 计算州的平均人口
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state'},
      document_count:{$sum:1},
      pop:{$sum:'$pop'}  
    }
  },
  {
    $group:{
      _id:null,
      state_count:{$sum:1},
      state_avg_pop: {
        $avg: '$pop'
      }
    }
  }
]);

// 计算每个州中有多少个城市
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state', city:'$city'},
      document_count: { $sum : 1 }
    }
  },
  {
    $group: {
      _id: {state:'$_id.state'},
      city_count: { $sum : 1  }
    }
  }
])


// 计算每个州中城市的平均人口
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state', city:'$city'},
      pop:{$sum:'$pop'}
    }
  },
  {
    $group:{
      _id:{state:'$_id.state'}, 
      city_count:{$sum:1},
      city_avg_pop: {
        $avg: '$pop'
      }
    }
  }
]);

// 计算人口最多的州和人口最少的州
// 方法1：使用max min
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state'},
      pop: {
        $sum: '$pop'
      }
    }
  },
  // {
  //   $project: {
  //     maxPop: { $max: '$pop'},
  //     smallestPop: {$min: '$pop'},
  //     biggestState: { $max: { maxpop: '$pop', state: '$_id.state'}},
  //     smallestState: { $min: { minpop: '$pop', state: '$_id.state'}},
  //   }
  // }
  {
    $group: {
      _id:null,
      maxPop: { $max: '$pop'},
      smallestPop: {$min: '$pop'},
      biggestState: { $max: { maxpop: '$pop', state: '$_id.state'}},
      smallestState: { $min: { minpop: '$pop', state: '$_id.state'}},
    }
  }
]);

// 方法二：使用sort
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state'},
      pop: {
        $sum : '$pop'
      }
    }
  },
  {
    $sort: { pop: 1 }
  },
  // {
  //   $project: {
  //     bigpop: {$last:'$pop'}, 
  //     bigcity:{$last:'$_id.state'} ,
  //     smallpop: {$first:'$pop'},
  //     smallcity:{$first:'$_id.state'}
  //   }
  // }
  {
    $group: {
      _id:null,
      bigpop: {$last:'$pop'}, 
      bigcity:{$last:'$_id.state'} ,
      smallpop: {$first:'$pop'},
      smallcity:{$first:'$_id.state'}
    }
  }
])

// 找到每个州中人口最多的城市和人口最少的城市。
// select state, MIN(pop) as smallestcity, MAX(POP) AS biggestcity from zipcodes group by state;
// 方法1：使用max/min
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state',city:'$city'},
      pop:{$sum:'$pop'}
    }
  },
  {
    $group: {
      _id:'$_id.state',
      biggestcity: { $max: { maxpop:'$pop', city:'$_id.city'} },
      smallestcity:{ $min: { minpop:'$pop', city: '$_id.city'} }
    }
  },
  // {
  //   $group: {
  //     _id: null,
  //     state_count: { $sum : 1},
  //     _biggestcity: '$biggestcity',
  //     _smallestcity: '$smallestcity'
  //   }
  // }
])

// 方法二：使用sort,$first,$last
db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: {state:'$state', city:'$city'},
      pop: { $sum: '$pop' }
    }
  },
  {
    $sort: { pop: 1 }
  },
  {
    $group: {
      _id: {state:'$_id.state'},
      biggestCity: {$last:{pop:'$pop', city:'$_id.city'}},
      smallestCity_pop: {$first:{pop:'$pop'}},
      smallestCity_city: {$first: '$_id.city'}
    }
  }
])

db.getCollection('zipcodes').aggregate([
  {
    $group: {
      _id: "$state",
      data: {
        $push: {
          pop: "$pop",
          otherField: "$$ROOT"
        }
      }
    }
  },
  {
    $sort: {
      pop: 1
    }
  },
  {
    $match: {
      state:'FL'
    }
  }
])


//
db.getCollection('userPreference').insertMany([
{
    _id : "jane",
  joined : ISODate("2011-03-02"),
  likes : ["golf", "racquetball"]
},
{
  _id : "joe",
  joined : ISODate("2012-07-02"),
  likes : ["tennis", "golf", "swimming"]
}
]) 

db.getCollection('userPreference').aggregate([
  {
    $unwind: "$likes" // 将数组展开
  }
])
// 找到5个最受欢迎的爱好
db.getCollection('userPreference').aggregate([
  {
    $unwind: "$likes" // 将数组展开
  },
  {
    $group: {
    _id: {likes:'$likes'},
    sum: {$sum:1}
  }},
  {
    $sort: {
      sum: -1
    }
  },
  {
    $limit: 5
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
