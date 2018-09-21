/* index.js */

function myFirstGraph() {
	var DATA_COUNT = 8;
	Samples.srand(18);

	function generatePoint() {
		return {
			x: Samples.rand(-100, 100),
			y: Samples.rand(-50, 50),
			v: Samples.rand(15, 100),
			l: 'Daumesnil'
		};
	}

	function generateData() {
		var data = [];
		for (var i = 0; i < DATA_COUNT; ++i) {
			data.push(generatePoint());
		}
		return data;
	}

	var ctx = document.getElementById("myChart").getContext('2d');
var myChart = new Chart(ctx, {
			type: 'bubble',
			data: {
				datasets: [{
					backgroundColor: Samples.color(0),
					borderColor: Samples.color(0),
					data: generateData()
				}, {
					backgroundColor: Samples.color(1),
					borderColor: Samples.color(1),
					data: generateData()
				}]
			},
			options: {
				title: {
				display: false,
				text: 'Stations de Metro de Paris'
			  }, scales: {
				yAxes: [{ 
				  scaleLabel: {
					display: false,
					labelString: "lati"
				  },
				  gridLines: {
					  drawBorder: false,
					display: false
				  },
				  ticks: {
						display: false
					}
				}],
				xAxes: [{ 
				  scaleLabel: {
					display: false,
					labelString: "longi"
				  },
				  gridLines: {
					  drawBorder: false,
					display: false
				  },
				  ticks: {
						display: false
					}
				}]
			  }, 
				plugins: {
					datalabels: {
						anchor: function(context) {
							return 'end';
						},
						align: function(context) {
							return 'end';
						},
						color: function(context) {
							var value = context.dataset.data[context.dataIndex];
							return context.dataset.backgroundColor;
						},
						font: {
							weight: 'bold'
						},
						formatter: function(value) {
							return value.l;
						},
						offset: 2,
						padding: 0
					}
				}
			}
		});
}

function initDefaults() {
		Chart.helpers.merge(Chart.defaults.global, {
			aspectRatio: 1,
			tooltips: false,
			layout: {
				padding: {
					top: 42,
					right: 16,
					bottom: 32,
					left: 8
				}
			},
			elements: {
				point: {
					radius: function(context) {
						var value = context.dataset.data[context.dataIndex];
						var size = context.chart.width;
						var base = Math.abs(value.v) / 100;
						return (size / 24) * base;
					}
				}
			},
			plugins: {
				legend: false,
				title: false
			}
		});
}


$(document).ready(function() {
	
"use strict";
var msg = "hello JavaScript";
console.log(msg);
//var resultsDiv = document.getElementById("results");
//resultsDiv.innerHTML = "<p>Hello Marine. This is from JavaScript</p>";

var resultList = $("#resultList"); //$ is alias for jQuery
resultList.text("This is from jQuery");

initDefaults();

myFirstGraph();

var toggleButton = $("#toggleButton");
toggleButton.on("click", function () {
	resultList.toggle(500);
	if (toggleButton.text() == "Hide") toggleButton.text("Show");
	else toggleButton.text("Hide");
});

var listItems = $("header nav li");
listItems.css("font-weight", "bold");//of course it would be better to put this in css file
listItems.filter(":first").css("font-size", "18px");

/*
var result = {
	name: "jQuery",
	language: "JavaScript",
	score: 4.5,
	showLog: function () {
		
	},
	owner: {
		login: "olivierRoussel",
		id: 123456
	}
};

result.phoneNumber = "123-456-7890"; //adding a new property !

console.log(result.phoneNumber);

var results = [];
results.push(result);
*/

$("#gitHubSearchForm").on("submit", function() {

	var searchPhrase = $("#searchPhrase").val();
	var useStars = $("#useStars").val();
	var langChoice = $("#langChoice").val();
	
	if (searchPhrase) {
		
		resultList.text("Performing search...");
		
		//var gitHubSearch = "https://api.github.com/search/repositories?q=jquery+language:javascript&sort=stars";

		var gitHubSearch = "https://api.github.com/search/repositories?q=" + encodeURIComponent(searchPhrase);
		
		if (langChoice != "All") {
			gitHubSearch += "+language:" + encodeURIComponent(langChoice);
		}
		
		if (useStars) {
			gitHubSearch += "&sort=stars";
		}
		
		$.get(gitHubSearch)
			.done(function(r) {
			//console.log(r.items.length);
			displayResults(r.items);
			})
			.fail(function (err) {
				console.log("Failed to query GitHib");
			})
			.done(function () {
				//finally
			});
	}
	return false;
});
/*
var results = [{
	name: "jQuery",
	language: "JavaScript",
	score: 4.5,
	showLog: function () {
		
	},
	owner: {
		login: "olivierRoussel",
		id: 123456
	}},
	{
	name: "jQuery UI",
	language: "JavaScript",
	score: 3.5,
	showLog: function () {
		
	},
	owner: {
		login: "olivierRoussel",
		id: 123456
	}
	}
];
*/


function displayResults(results) {
	resultList.empty();
	$.each(results, function(i, item) {
		
		var newResult = $("<div class='result'>" +
			"<div class='title'>" + item.name + "</div>" +
			"<div>Language: " + item.language + "</div>" +
			"<div>Owner: " + item.owner.login + "</div>" +
			"</div>");
			
		newResult.hover(function () {
			//make it darker
			$(this).css("background-color", "lightgray");
		}, function () {
			//reverse
			$(this).css("background-color", "transparent");
		});
			
		resultList.append(newResult);
	});
}

//console.log(results.length);
//console.log(results[0].name);

//for (var x = 0; x < results.length ; x++) {
//	var result = results[x];
	//accepte break et continue
//	console.log(result.name);
//}

/*
console.log("msg is " + typeof(msg));

var none;
if (none == undefined) {
	console.log("none is undefined");
}

var aNumber=10;

if (aNumber == "10")
	console.log("aNumber can be compared to string 10");

if (aNumber !== "10")
	console.log("But aNumber is not equal to string 10");

function showMsg(msg, more) {
	if (more)
		console.log("showMsg : " + msg + more);
	else
		console.log("showMsg : " + msg);
}

showMsg("some information");
showMsg("some information" + " and some more");

function showMsgThen(msg, callback) {
	showMsg(msg);
	callback();
}

showMsgThen("showMsgThen called", function () {
	console.log("callback called");
});
*/

});
