// Michael Coughlin
// hiimmichael.com
// 2019 

$( document ).ready(function() { 
    $("#sun").hide();
    $("#moon").hide();
    $("#sunset").hide();
    $("#sunrise").hide();
            
    $('img#wicon').on('load', function(){
        $("#wicon").fadeIn(500);
        $("#expect").fadeIn(2000);
        $("#temp").fadeIn(500);
        $("#hi_and_lo").fadeIn(1500);
        $("#humidity").fadeIn(1500);
        $("#wind").fadeIn(1500);
        $("#clouds").fadeIn(1500);
        $("#sun").fadeIn(2000);
        $("#moon").fadeIn(2000);
        $("#sunrise").fadeIn(2000);
        $("#sunset").fadeIn(2000);
    });
    
    $('body').gradientify({
        gradients: [
            { start: [91,137,48], stop: [86,130,3] },
            { start: [0,73,133], stop: [3,80,150] },
            { start: [185,130,6], stop: [202,135,9] }
        ],
        transition_time: 5
    });
});   

$(function() {
    $('#light').bind('change', function() {
        $.getJSON('/light',
            function(err, data) {
                }).success(function(result) {
                    console.log(result);
                     
                    if (result.is_grow_light_on === 'True') {
                        $("#light_status").text('Grow Lights On');
                        $("#light").prop("checked", 1);
                    } else {
                        $("#light_status").text('Grow Lights Off');
                        $("#light").prop("checked", 0);
                    }
            
                }).error(function(error){
                    console.log(error);
                });
            return false;
            });
        });
 
$(function() {
    $('#water').bind('change', function() {
        $.getJSON('/water',
            function(err, data) {
                }).success(function(result) {
                    console.log(result);

                    if (result.is_water_pump_on === 'True') {
                        $("#water_status").text('Water Pump On');
                        $("#water").prop("checked", 1);
                    } else {
                        $("#water_status").text('Water Pump Off');
                        $("#water").prop("checked", 0);
                    }
                
                }).error(function(error){
                    console.log(error);
                });
            return false;
            });
        });

$(function() {
    $('#auto').bind('change', function() {
        $.getJSON('/auto',
            function(err, data) {
                }).success(function(result) {
                    console.log(result);

                    if (result.is_sitter_mode_enabled === 'True') {
                        $("#auto_status").text('Plant Sitter On');
                        $("#auto").prop("checked", 1);
                    } else {
                        $("#auto_status").text('Plant Sitter Off');
                        $("#auto").prop("checked", 0);
                    }
                }).error(function(error){
                    console.log(error);
                });
            return false;
            });
        });
